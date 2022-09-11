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

void Human::Move()
{
	Input* input = Input::GetInstance();

	position_ = human_->GetPosition();
	XMFLOAT2 vector = { input->GetMousePoint().x - position_.x, input->GetMousePoint().y - position_.y };
	float v = 0.0f;

	v = sqrtf((vector.x * vector.x) + (vector.y * vector.y));
	vector = { (vector.x / v) * speed_.y, (vector.y / v) * speed_.y };

	if (vector.x > 0)
	{
		speed_.x = 0.1f;
	}
	else
	{
		speed_.x = -0.1f;
	}

	position_.x += speed_.x;
	position_.y -= speed_.y;

	human_->SetPosition(position_);
}