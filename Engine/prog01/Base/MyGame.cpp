#include "MyGame.h"
#include "MapChip.h"
#include "SceneFactory.h"
#include "SpriteFactory.h"
#include "FbxFactory.h"
#include "ObjFactory.h"

void MyGame::Initialize()
{
	//���N���X�̏�����
	BaseGame::Initialize();

	//�Q�[���ŕK�v�ȃ}�b�v�f�[�^�̃��[�h
	//MapChip::GetInstance()->CsvLoad();
	//�Q�[���ŕK�v�ȉ摜�̃��[�h
	SpriteFactory::GetInstance()->Initialize();
	//�Q�[���ŕK�v�ȃ��f��(.fbx)�̃��[�h
	FbxFactory::GetInstance()->Initialize();
	//�Q�[���ŕK�v�ȃ��f��(.obj)�̃��[�h
	ObjFactory::GetInstance()->Initialize();
	//�Q�[���ŕK�v�ȃT�E���h�̃��[�h
	Audio::GetInstance()->LoadWave(0, "Resources/audio/bonus.wav");
	Audio::GetInstance()->LoadWave(1, "Resources/audio/cursor.wav");
	Audio::GetInstance()->LoadWave(2, "Resources/audio/drill.wav");
	Audio::GetInstance()->LoadWave(3, "Resources/audio/finish.wav");
	Audio::GetInstance()->LoadWave(4, "Resources/audio/fossil.wav");
	Audio::GetInstance()->LoadWave(5, "Resources/audio/go.wav");
	Audio::GetInstance()->LoadWave(6, "Resources/audio/mining.wav");
	Audio::GetInstance()->LoadWave(7, "Resources/audio/power.wav");
	Audio::GetInstance()->LoadWave(8, "Resources/audio/recov.wav");
	Audio::GetInstance()->LoadWave(9, "Resources/audio/start.wav");
	Audio::GetInstance()->LoadWave(10, "Resources/audio/stone.wav");
	Audio::GetInstance()->LoadWave(11, "Resources/audio/game.wav");
	Audio::GetInstance()->LoadWave(12, "Resources/audio/title.wav");

	// �V�[���̏�����
	//�V�[���t�@�N�g���𐶐����A�}�l�[�W���[�ɃZ�b�g
	sceneFactory = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);
	//�V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	SceneManager::GetInstance()->ChangeScene("TitleScene");
}

void MyGame::Finalize()
{
	// �V�[���̏I��
	SceneManager::GetInstance()->Finalize();
	//�eFactory�̉��
	FbxFactory::GetInstance()->Finalize();
	ObjFactory::GetInstance()->Finalize();
	//���N���X�̉��
	BaseGame::Finalize();
}

void MyGame::Update()
{
	//���N���X�̍X�V
	BaseGame::Update();
}

void MyGame::Draw()
{
	BaseGame::Draw();
}