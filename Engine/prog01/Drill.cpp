#include "Drill.h"

#include "FbxFactory.h"
#include "ObjFactory.h"

void Drill::Initialize(XMFLOAT3 hPosition, XMFLOAT3 pPosition, float saveAngle)
{
	object_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sphere"));

	position_ = hPosition;
	scale_ = START_SCALE;

	object_->SetPosition(position_);
	object_->SetScale(scale_);

	float angle = saveAngle;

	XMFLOAT2 length = { 2.0f, 2.0f };

	float rad = angle * 3.14159265359f / 180.0f;
	XMFLOAT2 around = { cos(rad) * length.x / 1.0f, -sin(rad) * length.y / 1.0f };

	speed_.x = around.x;
	speed_.y = around.y;
}

void Drill::Finalize()
{
}

void Drill::Update(XMFLOAT3 pPosition)
{
	position_ = object_->GetPosition();

	position_.x += speed_.x;
	position_.y += speed_.y;

	object_->SetPosition(position_);

	if (count_ >= 6 || position_.x > 13 || position_.x < -43 || pPosition.y - 100 > position_.y)
	{
		flag_ = true;
	}

	object_->Update();
}

void Drill::Draw()
{
	object_->Draw();
}

void Drill::SetPosition(XMFLOAT3 position)
{
	position_ = position;
	object_->SetPosition(position_);
}

void Drill::SetRotation(XMFLOAT3 rotation)
{
	rotation_ = rotation;
	object_->SetRotation(rotation_);
}

void Drill::SetScale(XMFLOAT3 scale)
{
	scale_ = scale;
	object_->SetScale(scale_);
}
