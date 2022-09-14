#include "TitleScene.h"
#include "SceneManager.h"
#include "DirectXCommon.h"
#include "ObjFactory.h"
#include "Ease.h"
#include "ChangeScene.h"

TitleScene::~TitleScene()
{
	Finalize();
}

void TitleScene::Initialize()
{
	sprite_ = Sprite::Create(1, { 0.0f,0.0f }, { 1,1,1,1 }, {-1.0f,-0.5f});
	backGround_ = Sprite::Create(11, { 0.0f,0.0f });

	ChangeScene::GetInstance()->Initialize();
}

void TitleScene::Finalize()
{
}

void TitleScene::Update()
{
	Input* input = Input::GetInstance();

	if (!isBgmFalg_)
	{
		Audio::GetInstance()->LoopPlayWave(11);
		isBgmFalg_ = true;
	}
	else
	{
		audioTimer_++;

		if (audioTimer_ >= 6140)
		{
			maxVolume_ = true;
		}

		if (!maxVolume_)
		{
			volume_ += 0.01f;

			if (volume_ < 1.0f)
			{
				Audio::GetInstance()->LoopSetVolume(1, volume_);
			}
			else
			{
				volume_ = 1.0f;
			}
		}
		else
		{
			volume_ -= 0.01f;
			if (volume_ > 0.0f)
			{
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
	
	if (input->TriggerPadKey(BUTTON_A) || input->TriggerKey(DIK_SPACE))
	{
		ChangeScene::GetInstance()->SetIsChange(true);
	}

	if (ChangeScene::GetInstance()->GetIsIn())
	{
		SceneManager::GetInstance()->ChangeScene("GameScene");
	}

	ChangeScene::GetInstance()->Update();
}

void TitleScene::Draw()
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
	DebugText::GetInstance()->DrawAll(cmdList);
	sprite_->Draw();
	ChangeScene::GetInstance()->Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}

void TitleScene::EffectDraw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
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

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}