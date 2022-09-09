#include "Block.h"

#include "FbxFactory.h"
#include "ObjFactory.h"

void Block::Initialize(int type, XMFLOAT3 position)
{
	if (type == SOIL)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("cube"));
		type_ = SOIL;
	}
	else if (type == ROCK)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("cube"));
		type_ = ROCK;
	}
	else if (type == COAL)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("cube"));
		type_ = COAL;
	}
	else if (type == IRONSTONE)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("cube"));
		type_ = IRONSTONE;
	}
	else if (type == GOLDORE)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("cube"));
		type_ = GOLDORE;
	}
	else if (type == DIAMOND)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("cube"));
		type_ = DIAMOND;
	}
	else if (type == FOSSIL)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("cube"));
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