#include "Drill.h"

#include "FbxFactory.h"
#include "ObjFactory.h"

void Drill::Initialize(XMFLOAT3 hPosition, XMFLOAT3 pPosition, XMFLOAT2 mPosition)
{
	object_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sphere"));

	position_ = hPosition;
	scale_ = START_SCALE;

	object_->SetPosition(position_);
	object_->SetScale(scale_);

	float angle = mPosition.x;

	if (angle <= -90)
	{
		angle = -90;
	}
	else if (angle >= 90)
	{
		angle = 90;
	}
	XMFLOAT2 length = { 2.0f, 2.0f };

	float rad = (angle + 90) * 3.14159265359f / 180.0f;
	XMFLOAT2 around = { -cos(rad) * length.x / 1.0f, -sin(rad) * length.y / 1.0f };

	speed_.x = around.x;
	speed_.y = around.y;
}

void Drill::Finalize()
{
}

void Drill::Update()
{
	position_ = object_->GetPosition();

	position_.x += speed_.x;
	position_.y += speed_.y;

	object_->SetPosition(position_);

	if (count_ >= 10 || position_.x >= 15 || position_.x <= -15)
	{
		flag_ = true;
	}

	object_->Update();
}

void Drill::Draw()
{
	object_->Draw();
}
