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
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion 背景スプライト描画
#pragma region 3Dオブジェクト描画
	// 3Dオブクジェクトの描画
	Object3d::PreDraw(cmdList);

	Object3d::PostDraw();
#pragma endregion 3Dオブジェクト描画
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	ChangeScene::GetInstance()->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}

void ClearScene::EffectDraw()
{
}