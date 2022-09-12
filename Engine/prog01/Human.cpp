#include "Human.h"
#include "FbxFactory.h"
#include "ObjFactory.h"

#include "DirectXCommon.h"
#include "Input.h"
#include "Vector.h"
#include "Collision.h"

#include "DebugText.h"

std::unique_ptr<Human> Human::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Human* human = new Human();
	if (human == nullptr)
	{
		return nullptr;
	}
	human->Initialize();

	return std::unique_ptr<Human>(human);
}

void Human::Initialize()
{
	human_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sphere"));
	human_->SetPosition({ 0,3,0 });
	human_->SetScale(scale_);
}

void Human::Finalize()
{
}

void Human::Update()
{
	human_->Update();
}

void Human::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();

	human_->Draw();
}

void Human::Move(float angle, XMFLOAT2 speed)
{
	Input* input = Input::GetInstance();

	position_ = human_->GetPosition();

	float hSpeed = (float)sqrtf((speed.x * speed.x) + (speed.y * speed.y));

	position_.x += sinf((angle * 3.14) / 180.0f) * hSpeed * 0.5f;
	position_.y -= 0.2f;

	human_->SetPosition(position_);
}

void Human::SetPosition(XMFLOAT3 position)
{
	position_ = position;
	human_->SetPosition(position_);
}

void Human::SetRotation(XMFLOAT3 rotation)
{
	rotation_ = rotation;
	human_->SetRotation(rotation_);
}

void Human::SetScale(XMFLOAT3 scale)
{
	scale_ = scale;
	human_->SetScale(scale_);
}
