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
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
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
	// �R�}���h���X�g�̎擾
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
	vector = { (vector.x / v) * speed_, (vector.y / v) * speed_ };

	position_.x += vector.x;
	position_.y -= speed_;

	human_->SetPosition(position_);
}
