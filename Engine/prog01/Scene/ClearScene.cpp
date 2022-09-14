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
		sprite_[i]->SetPosition({ i * 50.0f , 0 });
	}

	backGround_ = Sprite::Create(12, { 0.0f,0.0f });
}

void ClearScene::Finalize()
{
}

void ClearScene::Update()
{
	Input* input = Input::GetInstance();

	if (!flag)
	{
		if (ChangeScene::GetInstance()->GetIsIn() && !ChangeScene::GetInstance()->GetIsOut())
		{
			ChangeScene::GetInstance()->SetIsChange(false);
		}

		if (input->TriggerPadKey(BUTTON_A) || input->TriggerKey(DIK_SPACE))
		{
			ChangeScene::GetInstance()->SetIsChange(true);
			flag = true;
		}
	}
	else
	{
		if (ChangeScene::GetInstance()->GetIsIn() && !ChangeScene::GetInstance()->GetIsOut())
		{
			if (isSelection)
			{
				SceneManager::GetInstance()->ChangeScene("TitleScene");
			}
			else
			{
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

	//ChangeScene::GetInstance()->Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}

void ClearScene::EffectDraw()
{
}