#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "Collision.h"
#include "SphereCollider.h"
#include "MeshCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "ContactableObject.h"

#include "SceneManager.h"
#include "FbxFactory.h"
#include "ObjFactory.h"

#include "DirectXCommon.h"
#include "DebugText.h"
#include "Audio.h"
#include "Input.h"
#include "MapChip.h"

using namespace DirectX;

GameScene::~GameScene()
{
	Finalize();
}

void GameScene::Initialize()
{
	collisionManager_ = CollisionManager::GetInstance();

	// カメラ生成
	camera_ = std::make_unique<Camera>(WinApp::window_width, WinApp::window_height);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera_.get());
	// FBXオブジェクトにカメラをセット
	FbxObject3d::SetCamera(camera_.get());

	// 背景スプライト生成
	sprite_ = Sprite::Create(1, { 0.0f,0.0f });
	sprite_->SetSize({ 100.0f,100.0f });
	sprite_->SetPosition({ 100.0f,100.0f });

	// パーティクルマネージャ生成
	particleMan_ = ParticleManager::Create(DirectXCommon::GetInstance()->GetDevice(), camera_.get());

	//ライト生成
	light_ = LightGroup::Create();
	//オブジェクトにライトをセット
	Object3d::SetLight(light_.get());
	FbxObject3d::SetLight(light_.get());
	light_->SetDirLightActive(0, true);
	light_->SetDirLightActive(1, false);
	light_->SetDirLightActive(2, false);
	light_->SetPointLightActive(0, false);
	light_->SetPointLightActive(1, false);
	light_->SetPointLightActive(2, false);
	light_->SetCircleShadowActive(0, false);
	light_->SetDirLightDir(0, { 0,0,1,0 });

	// 3Dオブジェクト生成
	player_ = Human::Create();
	hit_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sphere"));

	MapChip::GetInstance()->CsvLoad(10, 10, "sampleMap");

	//BlockCreate("sampleMap");

	// FBXオブジェクト生成

	// カメラ注視点をセット
	camera_->SetTarget({ 0, 0, 0 });
	camera_->SetEye({ 0,0,-50 });
}

void GameScene::Finalize()
{
	for (auto a : box_)
	{
		delete a;
	}
	box_.clear();
	MapChip::GetInstance()->Finalize();
}

void GameScene::Update()
{
	Input* input = Input::GetInstance();
	light_->Update();
	particleMan_->Update();
	// ステージ生成
	StageCreate();
	// ヒットボックス
	HitBox();
	// ブロックの破壊
	BlockBreak();
	// プレイヤーの動き
	player_->Move();

	if (input->PushMouseLeft())
	{
		player_->SetSpeed_(0.2f);
	}
	else
	{
		player_->SetSpeed_();
	}


	player_->Update();
	for (auto a : box_)
	{
		a->Update();
	}
	
	hit_->Update();
	CameraMove();
	// 全ての衝突をチェック
	collisionManager_->CheckAllCollisions();

	DebugText::GetInstance()->VariablePrint(0, 0, "playerPos", player_->GetPosition().y, 1.0f);
	DebugText::GetInstance()->VariablePrint(0, 16, "box_.size", box_.size(), 1.0f);
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	
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
#pragma region 3Dオブジェクト(FBX)描画

#pragma endregion 3Dオブジェクト(FBX)描画
#pragma region パーティクル
	// パーティクルの描画

#pragma endregion パーティクル
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}

void GameScene::EffectDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion 背景スプライト描画
#pragma region 3Dオブジェクト描画
	// 3Dオブクジェクトの描画
	Object3d::PreDraw(cmdList);
	player_->Draw();
	hit_->Draw();
	if (!flag)
	{
		for (auto a : box_)
		{
			a->Draw();
		}
	}
	Object3d::PostDraw();
#pragma endregion 3Dオブジェクト描画
#pragma region 3Dオブジェクト(FBX)描画

#pragma endregion 3Dオブジェクト(FBX)描画
#pragma region パーティクル
	// パーティクルの描画
	particleMan_->Draw(cmdList);
#pragma endregion パーティクル
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}

void GameScene::BlockCreate(std::string fName)
{
	for (int i = 0; i < MapChip::GetInstance()->GetMapChipMaxXY(fName).y; i++)
	{
		for (int j = 0; j < MapChip::GetInstance()->GetMapChipMaxXY(fName).x; j++)
		{
			if (MapChip::GetInstance()->GetChipNum(j, i, fName) != 0)
			{
				Block* a = new Block();
				a->Initialize(MapChip::GetInstance()->GetChipNum(j, i, fName), { (j - MapChip::GetInstance()->GetMapChipMaxXY(fName).x / 2) * 3, ((i - MapChip::GetInstance()->GetMapChipMaxXY(fName).y / 2) * 3) - (30 * createCount_), 0 });
				box_.push_back(a);
			}
		}
	}
}

void GameScene::CameraMove()
{
	// カメラ注視点をセット
	camera_->SetTarget({ 0, player_->GetPosition().y - 10, 0 });
	camera_->SetEye({ 0, player_->GetPosition().y - 10, -50 });
	camera_->Update();
}

void GameScene::BlockBreak()
{
	int count = 0;
	for (auto a : box_)
	{
		Box enemy;
		enemy.center = { a->GetPosition().x, a->GetPosition().y, a->GetPosition().z, 0 };
		enemy.scale = a->GetScale();

		Sphere player;
		player.center = { hit_->GetPosition().x, hit_->GetPosition().y, hit_->GetPosition().z, 0 };

		if (a->GetType() == Block::SOIL && Collision::CheckSphere2Box(player, enemy))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}
		else if (a->GetType() == Block::ROCK && Collision::CheckSphere2Box(player, enemy))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}
		else if (a->GetType() == Block::COAL && Collision::CheckSphere2Box(player, enemy))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}
		else if (a->GetType() == Block::IRONSTONE && Collision::CheckSphere2Box(player, enemy))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}
		else if (a->GetType() == Block::GOLDORE && Collision::CheckSphere2Box(player, enemy))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}
		else if (a->GetType() == Block::DIAMOND && Collision::CheckSphere2Box(player, enemy))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}
		else if (a->GetType() == Block::FOSSIL && Collision::CheckSphere2Box(player, enemy))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}

		//後始末
		if (a->GetPosition().y >= (player_->GetPosition().y + 10))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}
		count++;
	}
	
}

void GameScene::HitBox()
{
	Input* input = Input::GetInstance();

	float angle = input->GetMousePoint().x;

	if (angle <= -90)
	{
		angle = -90;
	}
	else if (angle >= 90)
	{
		angle = 90;
	}

	float rad = (angle + 90) * 3.14159265359f / 180.0f;
	XMFLOAT2 around = { -cos(rad) * 1.5f / 1.0f, -sin(rad) * 1.5f / 1.0f };
	XMFLOAT3 wPos = hit_->GetPosition();
	wPos.x = around.x + player_->GetPosition().x;
	wPos.y = around.y + player_->GetPosition().y;

	hit_->SetPosition(wPos);
}

void GameScene::StageCreate()
{
	if (player_->GetPosition().y <= -createCount_ * 10 && box_.size() <= 150)
	{
		createCount_++;
		BlockCreate("sampleMap");
	}
}
