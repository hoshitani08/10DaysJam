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
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	backGround_->Draw();
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

	for (int i = 0; i < sprite_.size(); i++)
	{
		sprite_[i]->Draw();
	}

	//ChangeScene::GetInstance()->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}

void ClearScene::EffectDraw()
{
}