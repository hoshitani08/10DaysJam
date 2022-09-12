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
	light_->SetDirLightDir(0, { 0,-1,1,0 });

	// 3Dオブジェクト生成
	player_ = Human::Create();

	for (int i = 0; i < hit_.size(); i++)
	{
		hit_[i] = Object3d::Create(ObjFactory::GetInstance()->GetModel("sphere"));
		hit_[i]->SetScale({ 2,2,2 });
	}

	MapChip::GetInstance()->CsvLoad(15, 15, "map01");
	MapChip::GetInstance()->CsvLoad(15, 15, "map02");
	MapChip::GetInstance()->CsvLoad(15, 15, "map03");
	MapChip::GetInstance()->CsvLoad(15, 15, "map04");
	MapChip::GetInstance()->CsvLoad(15, 15, "map05");
	MapChip::GetInstance()->CsvLoad(15, 15, "map06");
	MapChip::GetInstance()->CsvLoad(15, 15, "map07");
	MapChip::GetInstance()->CsvLoad(15, 15, "map08");
	MapChip::GetInstance()->CsvLoad(15, 15, "map09");
	MapChip::GetInstance()->CsvLoad(15, 15, "map10");
	MapChip::GetInstance()->CsvLoad(15, 15, "map11");
	MapChip::GetInstance()->CsvLoad(15, 15, "map12");

	//BlockCreate("sampleMap");

	// FBXオブジェクト生成

	//UI生成
	ui_ = std::make_unique<UserInterface>();
	ui_->Initialize();

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

	for (auto a : drill_)
	{
		delete a;
	}
	drill_.clear();

	MapChip::GetInstance()->Finalize();
}

void GameScene::Update()
{
	Input* input = Input::GetInstance();
	light_->Update();
	particleMan_->Update();
	// ステージ生成
	StageCreate();
	if (ui_->GetFuel() > 0)
	{
		// ヒットボックス
		HitBox();
		// 鉱石の効果
		OreBuff();
		// 左クリック
		SpecialMove();
		// ブロックの破壊
		BlockBreak();
		// プレイヤーの動き
		player_->Move(input->PadStickAngle() + 90, input->PadStickGradient());
	}

	for (auto a : drill_)
	{
		a->Update();
	}

	player_->Update();
	for (auto a : box_)
	{
		a->Update();
	}
	ui_->Update();
	for (int i = 0; i < hit_.size(); i++)
	{
		hit_[i]->Update();
	}
	CameraMove();
	// 全ての衝突をチェック
	collisionManager_->CheckAllCollisions();
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
	for (int i = 0; i < hit_.size(); i++)
	{
		if (!goldOre.flag && i != 0)
		{
			break;
		}
		hit_[i]->Draw();
	}

	for (auto a : drill_)
	{
		a->Draw();
	}

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
				a->Initialize(MapChip::GetInstance()->GetChipNum(j, i, fName), { (j - MapChip::GetInstance()->GetMapChipMaxXY(fName).x / 2) * 4, (((i - MapChip::GetInstance()->GetMapChipMaxXY(fName).y / 2) * 4) - (60 * createCount_) + 30), 0 });
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

		for (int i = 0; i < hit_.size(); i++)
		{
			if (!goldOre.flag && i != 0)
			{
				break;
			}

			Sphere player;
			player.center = { hit_[i]->GetPosition().x, hit_[i]->GetPosition().y, hit_[i]->GetPosition().z, 0 };
			player.radius = 2;

			if (a->GetType() == Block::SOIL && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);
			}
			else if (a->GetType() == Block::ROCK && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);

				if (ironStone.flag)
				{
					ui_->SetSaveFuel(-25);
				}
			}
			else if (a->GetType() == Block::COAL && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);

				ui_->SetSaveFuel(100);
			}
			else if (a->GetType() == Block::IRONSTONE && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);

				ironStone.flag = true;
			}
			else if (a->GetType() == Block::GOLDORE && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);

				goldOre.flag = true;
			}
			else if (a->GetType() == Block::FOSSIL && Collision::CheckSphere2Box(player, enemy))
			{
				ui_->AddScore(1000);
				delete a;
				box_.erase(box_.begin() + count);

				int typeCount = 0;
				typeCount = rand() % 3;

				if (typeCount == 1)
				{
					// サーベルタイガー
					typeCount = rand() % 2;
					if (typeCount == 0)
					{
						ui_->SBoneScore({ true, false });
					}
					else
					{
						ui_->SBoneScore({ false, true });
					}
				}
				else if (typeCount == 2)
				{
					// ティラノサウルス
					typeCount = rand() % 3;
					if (typeCount == 0)
					{
						ui_->TBoneScore({ true, false });
					}
					else if (typeCount == 1)
					{
						ui_->TBoneScore({ false, true, false });
					}
					else
					{
						ui_->TBoneScore({ false, false ,true });
					}
				}
			}
		}

		//後始末
		if (a->GetPosition().y >= (player_->GetPosition().y + 15))
		{
			delete a;
			box_.erase(box_.begin() + count);
		}

		count++;
	}

	if (player_->GetPosition().y <= (4 * -dugCount_))
	{
		ui_->DugDistanceCalculate(1.0f);
		ui_->AddScore(10);
		ui_->SetSaveFuel(-10);
		dugCount_++;
	}
}

void GameScene::HitBox()
{
	Input* input = Input::GetInstance();

	if (input->PadStickGradient().x != 0.0f || input->PadStickGradient().y != 0.0f)
	{
		saveAngle = input->PadStickAngle();
	}

	if (saveAngle < 0)
	{
		saveAngle *= -1;
	}

	DebugText::GetInstance()->VariablePrint(0, 180, "saveAngle", saveAngle, 1.0f);

	if (saveAngle > 180)
	{
		saveAngle = 180;
	}
	else if (saveAngle <= 0)
	{
		saveAngle = 0;
	}

	float count = 0.0f;
	XMFLOAT2 length = { 2.0f, 2.0f };
	for (int i = 0; i < hit_.size(); i++)
	{
		if (i == 1)
		{
			count = 45;
		}
		else if (i == 2)
		{
			count = -45;
		}

		if (i != 0)
		{
			length.x = 3.0f;
			length.y = 3.0f;
		}

		float rad = (saveAngle + count) * 3.14159265359f / 180.0f;
		XMFLOAT2 around = { cosf(rad) * length.x / 1.0f, -sinf(rad) * length.y / 1.0f };
		XMFLOAT3 wPos = hit_[i]->GetPosition();

		wPos.x = around.x + player_->GetPosition().x;
		wPos.y = around.y + player_->GetPosition().y;

		hit_[i]->SetPosition(wPos);
	}
}

void GameScene::StageCreate()
{
	if (player_->GetPosition().y <= -createCount_ * 10 && box_.size() < 450)
	{
		createCount_++;
		int count = 0;
		do
		{
			count = rand() % 12;
		} while (count == 0);

		if (createCount_ <= 1)
		{
			count = 0;
		}

		if (count == 0)
		{
			BlockCreate("map01");
		}
		else if (count == 1)
		{
			BlockCreate("map02");
		}
		else if (count == 2)
		{
			BlockCreate("map03");
		}
		else if (count == 3)
		{
			BlockCreate("map04");
		}
		else if (count == 4)
		{
			BlockCreate("map05");
		}
		else if (count == 5)
		{
			BlockCreate("map06");
		}
		else if (count == 6)
		{
			BlockCreate("map07");
		}
		else if (count == 7)
		{
			BlockCreate("map08");
		}
		else if (count == 8)
		{
			BlockCreate("map09");
		}
		else if (count == 9)
		{
			BlockCreate("map10");
		}
		else if (count == 10)
		{
			BlockCreate("map11");
		}
		else if (count == 11)
		{
			BlockCreate("map12");
		}
	}
}

void GameScene::OreBuff()
{
	if (goldOre.flag && goldOre.timer > 0)
	{
		goldOre.timer--;
		DebugText::GetInstance()->Print("goldOre.flag = true", 0, 48, 1.0f);
	}
	else
	{
		goldOre.timer = 900;
		goldOre.flag = false;
		DebugText::GetInstance()->Print("goldOre.flag = false", 0, 48, 1.0f);
	}

	if (ironStone.flag && ironStone.timer > 0)
	{
		ironStone.timer--;
		DebugText::GetInstance()->Print("ironStone.flag = true", 0, 80, 1.0f);
	}
	else
	{
		ironStone.timer = 900;
		ironStone.flag = false;
		DebugText::GetInstance()->Print("ironStone.flag = false", 0, 80, 1.0f);
	}

	DebugText::GetInstance()->VariablePrint(0, 64 ,"goldOre.timer", goldOre.timer, 1.0f);
	DebugText::GetInstance()->VariablePrint(0, 96, "ironStone.timer", ironStone.timer, 1.0f);
}

void GameScene::SpecialMove()
{
	Input* input = Input::GetInstance();

	if (input->TriggerPadKey(BUTTON_A))
	{
		Drill* drill = new Drill;

		drill->Initialize(hit_[0]->GetPosition(), player_->GetPosition(), saveAngle);

		drill_.push_back(drill);
		ui_->SetSaveFuel(-50);
	}

	int count = 0;
	for (auto a : box_)
	{
		Box enemy;
		enemy.center = { a->GetPosition().x, a->GetPosition().y, a->GetPosition().z, 0 };
		enemy.scale = a->GetScale();

		int drillCount = 0;

		for (auto b : drill_)
		{
			XMFLOAT3 pos = b->GetPosition();

			Sphere player;
			player.center = { pos.x, pos.y, pos.z, 0 };
			player.radius = 2;

			if (a->GetType() == Block::SOIL && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);

				b->AddCount(1);
			}
			else if (a->GetType() == Block::ROCK && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);
				b->AddCount(1);
			}
			else if (a->GetType() == Block::COAL && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);
				b->AddCount(1);
				ui_->SetSaveFuel(100);
			}
			else if (a->GetType() == Block::IRONSTONE && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);
				b->AddCount(1);
				ironStone.flag = true;
			}
			else if (a->GetType() == Block::GOLDORE && Collision::CheckSphere2Box(player, enemy))
			{
				delete a;
				box_.erase(box_.begin() + count);
				b->AddCount(1);
				goldOre.flag = true;
			}
			else if (a->GetType() == Block::FOSSIL && Collision::CheckSphere2Box(player, enemy))
			{
				ui_->AddScore(1000);
				delete a;
				box_.erase(box_.begin() + count);
				b->AddCount(1);

				int typeCount = 0;
				typeCount = rand() % 3;

				if (typeCount == 1)
				{
					// サーベルタイガー
					typeCount = rand() % 2;
					if (typeCount == 0)
					{
						ui_->SBoneScore({ true, false });
					}
					else
					{
						ui_->SBoneScore({ false, true });
					}
				}
				else if (typeCount == 2)
				{
					// ティラノサウルス
					typeCount = rand() % 3;
					if (typeCount == 0)
					{
						ui_->TBoneScore({ true, false });
					}
					else if (typeCount == 1)
					{
						ui_->TBoneScore({ false, true, false });
					}
					else
					{
						ui_->TBoneScore({ false, false ,true });
					}
				}
			}

			if (b->GetFlag())
			{
				delete b;
				drill_.erase(drill_.begin() + drillCount);
			}

			drillCount++;
		}

		count++;
	}
}
