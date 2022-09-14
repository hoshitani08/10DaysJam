#include "Audio.h"
#include <fstream>
#include <cassert>

#pragma comment(lib,"xaudio2.lib")

Audio::Audio()
{

}

Audio::~Audio()
{
	xAudio2.Reset();

	//読み込み済みサウンドの波形データを解放
	for (auto& pair : soundDatas)
	{
		delete pair.second.pBuffer;
	}
}

Audio* Audio::GetInstance()
{
	static Audio instance;
	return &instance;
}

bool Audio::Initialize()
{
	HRESULT result;

	// XAudioエンジンのインスタンスを生成
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(result));

	// マスターボイスを生成
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	assert(SUCCEEDED(result));

	return true;
}

void Audio::LoadWave(int soundNumber, const char* filename)
{
	SoundData soundData = {};

	//ファイル入力ストリームのインスタンス
	std::ifstream file;
	//.wavファイルをバリナリモードで開く
	file.open(filename, std::ios_base::binary);
	//ファイルオープン失敗を検出する
	if (file.fail())
	{
		assert(0);
	}

	// RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0)
	{
		assert(0);
	}
	//タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0)
	{
		assert(0);
	}

	// Formatチャンクの読み込み
	FormatChunk format;
	file.read((char*)&format, sizeof(format));

	// Dataチャンクの読み込み
	Chunk data;
	file.read((char*)&data, sizeof(data));
	//JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK", 4) == 0)
	{
		//読み取り位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "data", 4) != 0)
	{
		assert(0);
	}

	// Dataチャンクのデータ部（波形データ）の読み込み
	soundData.pBuffer = new char[data.size];
	file.read(soundData.pBuffer, data.size);
	//波形データのサイズ記録
	soundData.dataSize = data.size;

	// Waveファイルを閉じる
	file.close();

	// 波形フォーマットの設定
	memcpy(&soundData.wfex, &format.fmt, sizeof(format.fmt));
	soundData.wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	//連想配列に要素を追加
	soundDatas.insert(std::make_pair(soundNumber, soundData));
}

void Audio::PlayWave(int soundNumber, float volume)
{
	SoundData& soundData = soundDatas[soundNumber];

	HRESULT result;

	// 波形フォーマットを元にSourceVoiceの生成
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex, 0, 2.0f, nullptr);
	pSourceVoice->SetVolume(volume);
	assert(SUCCEEDED(result));

	// 再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)soundData.pBuffer;
	buf.pContext = soundData.pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = soundData.dataSize;

	// 波形データの再生
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	assert(SUCCEEDED(result));

	result = pSourceVoice->Start();
	assert(SUCCEEDED(result));
}

void Audio::LoopPlayWave(int soundNumber, float volume)
{
	LoopSoundData loopSoundData;
	loopSoundData.soundData = soundDatas[soundNumber];

	HRESULT result;
	result = xAudio2->CreateSourceVoice(&loopSoundData.pSourceVoice, &loopSoundData.soundData.wfex, 0, 2.0f, nullptr);
	loopSoundData.pSourceVoice->SetVolume(volume);
	assert(SUCCEEDED(result));

	// 再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)loopSoundData.soundData.pBuffer;
	buf.pContext = loopSoundData.soundData.pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	buf.AudioBytes = loopSoundData.soundData.dataSize;

	// 波形データの再生
	result = loopSoundData.pSourceVoice->SubmitSourceBuffer(&buf);
	assert(SUCCEEDED(result));

	result = loopSoundData.pSourceVoice->Start();
	assert(SUCCEEDED(result));

	loopSoundDatas.push_back(loopSoundData);
}

void Audio::LoopStopWave(int soundNumber)
{
	HRESULT result;

	if (loopSoundDatas.size() != 0)
	{
		result = loopSoundDatas[soundNumber - 1].pSourceVoice->Stop();
		result = loopSoundDatas[soundNumber - 1].pSourceVoice->FlushSourceBuffers();
		result = loopSoundDatas[soundNumber - 1].pSourceVoice->SubmitSourceBuffer(&buf);
		loopSoundDatas.erase(loopSoundDatas.begin() + (soundNumber - 1));
	}
}

void Audio::LoopSetVolume(int soundNumber, float volume)
{
	HRESULT result;

	if (loopSoundDatas.size() != 0)
	{
		loopSoundDatas[soundNumber - 1].pSourceVoice->SetVolume(volume);
		result = loopSoundDatas[soundNumber - 1].pSourceVoice->SubmitSourceBuffer(&buf);
	}
	
}
