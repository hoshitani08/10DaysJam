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

	// �J��������
	camera_ = std::make_unique<Camera>(WinApp::window_width, WinApp::window_height);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera_.get());
	// FBX�I�u�W�F�N�g�ɃJ�������Z�b�g
	FbxObject3d::SetCamera(camera_.get());

	// �w�i�X�v���C�g����
	sprite_ = Sprite::Create(1, { 0.0f,0.0f });
	sprite_->SetSize({ 100.0f,100.0f });
	sprite_->SetPosition({ 100.0f,100.0f });

	// �p�[�e�B�N���}�l�[�W������
	particleMan_ = ParticleManager::Create(DirectXCommon::GetInstance()->GetDevice(), camera_.get());

	//���C�g����
	light_ = LightGroup::Create();
	//�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
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

	// 3D�I�u�W�F�N�g����
	player_ = Human::Create();
	hit_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sphere"));

	MapChip::GetInstance()->CsvLoad(10, 10, "sampleMap");

	//BlockCreate("sampleMap");

	// FBX�I�u�W�F�N�g����

	// �J���������_���Z�b�g
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
	// �X�e�[�W����
	StageCreate();
	// �q�b�g�{�b�N�X
	HitBox();
	// �u���b�N�̔j��
	BlockBreak();
	// �v���C���[�̓���
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
	// �S�Ă̏Փ˂��`�F�b�N
	collisionManager_->CheckAllCollisions();

	DebugText::GetInstance()->VariablePrint(0, 0, "playerPos", player_->GetPosition().y, 1.0f);
	DebugText::GetInstance()->VariablePrint(0, 16, "box_.size", box_.size(), 1.0f);
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	
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
#pragma region 3D�I�u�W�F�N�g(FBX)�`��

#pragma endregion 3D�I�u�W�F�N�g(FBX)�`��
#pragma region �p�[�e�B�N��
	// �p�[�e�B�N���̕`��

#pragma endregion �p�[�e�B�N��
#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}

void GameScene::EffectDraw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion �w�i�X�v���C�g�`��
#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�N�W�F�N�g�̕`��
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
#pragma endregion 3D�I�u�W�F�N�g�`��
#pragma region 3D�I�u�W�F�N�g(FBX)�`��

#pragma endregion 3D�I�u�W�F�N�g(FBX)�`��
#pragma region �p�[�e�B�N��
	// �p�[�e�B�N���̕`��
	particleMan_->Draw(cmdList);
#pragma endregion �p�[�e�B�N��
#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
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
	// �J���������_���Z�b�g
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

		//��n��
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
