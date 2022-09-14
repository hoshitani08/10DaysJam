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

}

void ClearScene::Finalize()
{
}

void ClearScene::Update()
{
	Input* input = Input::GetInstance();
	if (ChangeScene::GetInstance()->GetIsIn())
	{
		ChangeScene::GetInstance()->SetIsChange(false);
	}

	if (input->TriggerPadKey(BUTTON_A))
	{
		ChangeScene::GetInstance()->SetIsChange(true);
	}

	if (ChangeScene::GetInstance()->GetIsIn())
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

	ChangeScene::GetInstance()->Update();
}

void ClearScene::Draw()
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
	ChangeScene::GetInstance()->Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}

void ClearScene::EffectDraw()
{
}