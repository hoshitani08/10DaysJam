#include "Block.h"

#include "FbxFactory.h"
#include "ObjFactory.h"

void Block::Initialize(int type, XMFLOAT3 position)
{
	if (type == SOIL)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sampleDirt11"));
		type_ = SOIL;
	}
	else if (type == ROCK)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("stone"));
		type_ = ROCK;
	}
	else if (type == COAL)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sampleCoal1"));
		type_ = COAL;
	}
	else if (type == IRONSTONE)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sampleIron1"));
		type_ = IRONSTONE;
	}
	else if (type == GOLDORE)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sampleGold1"));
		type_ = GOLDORE;
	}
	else if (type == FOSSIL)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("block"));
		type_ = FOSSIL;
	}
	else if (type == LAVA)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("cube"));
		type_ = LAVA;
	}

	position_ = position;
	scale_ = START_SCALE;

	box_->SetScale(scale_);
	box_->SetPosition(position_);
}

void Block::Finalize()
{
}

void Block::Update()
{
	box_->Update();
}

void Block::Draw()
{
	box_->Draw();
}

void Block::SetPosition(XMFLOAT3 position)
{
	position_ = position;
	box_->SetPosition(position_);
}

void Block::SetRotation(XMFLOAT3 rotation)
{
	rotation_ = rotation;
	box_->SetRotation(rotation_);
}

void Block::SetScale(XMFLOAT3 scale)
{
	scale_ = scale;
	box_->SetScale(scale_);
}
