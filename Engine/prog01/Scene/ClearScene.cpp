#include "ClearScene.h"
#include "SceneManager.h"
#include "DirectXCommon.h"
#include "ObjFactory.h"
#include "Ease.h"
#include "ChangeScene.h"

ClearScene::~ClearScene()
{
	Finalize();
}

void ClearScene::Initialize()
{
	ui_ = std::make_unique<UserInterface>();
	ui_->Initialize();

	int score = ui_->GetScore();

	std::array<int, 6> count;
	count[0] = score / 100000;
	count[1] = (score - (count[0] * 100000)) / 10000;
	count[2] = (score - ((count[0] * 100000) + (count[1] * 10000))) / 1000;
	count[3] = (score - ((count[0] * 100000) + (count[1] * 10000) + (count[2] * 1000))) / 100;
	count[4] = (score - ((count[0] * 100000) + (count[1] * 10000) + (count[2] * 1000) + (count[3] * 100))) / 10;
	count[5] = (score - ((count[0] * 100000) + (count[1] * 10000) + (count[2] * 1000) + (count[3] * 100) + (count[4] * 10))) / 1;

	for (int i = 0; i < sprite_.size(); i++)
	{
		sprite_[i] = Sprite::Create(20 + count[i], { 0.0f,0.0f }, { 1,1,1,1 });
		sprite_[i]->SetPosition({ (i * 50.0f) + 500 , 300 });
	}

	backGround_ = Sprite::Create(12, { 0.0f,0.0f });

	result_ = Sprite::Create(30, { 500.0f,80.0f });
	score_ = Sprite::Create(31,  { 200.0f,300.0f });
	retry_ = Sprite::Create(32,  { 260.0f,500.0f });
	title_ = Sprite::Create(33,  { 830.0f,500.0f });
}

void ClearScene::Finalize()
{
}

void ClearScene::Update()
{
	Input* input = Input::GetInstance();

	if (!isBgmFalg_)
	{
		Audio::GetInstance()->LoopPlayWave(12);
		isBgmFalg_ = true;
	}
	else if (isBgmFalg_ && !flag)
	{
		audioTimer_++;

		if (audioTimer_ >= 6140)
		{
			maxVolume_ = true;
		}

		if (!maxVolume_)
		{
			if (volume_ < 1.0f)
			{
				volume_ += 0.01f;
				Audio::GetInstance()->LoopSetVolume(1, volume_);
			}
		}
		else
		{
			if (volume_ > 0.0f)
			{
				volume_ -= 0.01f;
				Audio::GetInstance()->LoopSetVolume(1, volume_);
			}
			else
			{
				maxVolume_ = false;
				volume_ = 0.0f;
				audioTimer_ = 0;
			}
		}
	}

	if (!flag)
	{
		if (ChangeScene::GetInstance()->GetIsIn() && !ChangeScene::GetInstance()->GetIsOut())
		{
			ChangeScene::GetInstance()->SetIsChange(false);
		}

		if (input->TriggerPadStickLeft() || input->TriggerPadStickRight())
		{
			if (isSelection)
			{
				isSelection = false;
			}
			else
			{
				isSelection = true;
			}
			Audio::GetInstance()->PlayWave(1, 0.2f);
		}

		if (input->TriggerPadKey(BUTTON_A) || input->TriggerKey(DIK_SPACE))
		{
			ChangeScene::GetInstance()->SetIsChange(true);
			flag = true;
		}

		if(isSelection)
		{
			title_->SetColor({ 3,0,0,1 });
			retry_->SetColor({ 1,1,1,1 });
		}
		else
		{
			title_->SetColor({ 1,1,1,1 });
			retry_->SetColor({ 3,0,0,1 });
		}
	}
	else
	{

		volume_ -= 0.05f;
		if (volume_ > 0.0f)
		{
			Audio::GetInstance()->LoopSetVolume(1, volume_);
		}
		if (ChangeScene::GetInstance()->GetIsIn() && !ChangeScene::GetInstance()->GetIsOut() && volume_ < 0.0f)
		{
			if (isSelection)
			{
				Audio::GetInstance()->LoopStopWave(1);
				SceneManager::GetInstance()->ChangeScene("TitleScene");
			}
			else
			{
				Audio::GetInstance()->LoopStopWave(1);
				SceneManager::GetInstance()->ChangeScene("GameScene");
			}
		}
	}
	ChangeScene::GetInstance()->Update();
}

void ClearScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	backGround_->Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion �w�i�X�v���C�g�`��
#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�N�W�F�N�g�̕`��
	Object3d::PreDraw(cmdList);

	Object3d::PostDraw();
#pragma endregion 3D�I�u�W�F�N�g�`��
#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	for (int i = 0; i < sprite_.size(); i++)
	{
		sprite_[i]->Draw();
	}

	result_->Draw();
	score_->Draw();
	retry_->Draw();
	title_->Draw();

	//ChangeScene::GetInstance()->Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}

void ClearScene::EffectDraw()
{
}