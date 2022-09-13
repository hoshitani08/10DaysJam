#include "Block.h"

#include "FbxFactory.h"
#include "ObjFactory.h"

void Block::Initialize(int type, XMFLOAT3 position)
{
	if (type == SOIL)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sampleDirt11"));
		blockType_ = SOIL;
	}
	else if (type == ROCK)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("stone"));
		blockType_ = ROCK;
	}
	else if (type == COAL)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sampleCoal1"));
		blockType_ = COAL;
	}
	else if (type == IRONSTONE)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sampleIron1"));
		blockType_ = IRONSTONE;
	}
	else if (type == GOLDORE)
	{
		box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("sampleGold1"));
		blockType_ = GOLDORE;
	}
	else if (type == FOSSIL)
	{
		blockType_ = FOSSIL;

		int typeCount = rand() % 3;
		if (typeCount == 0)
		{
			box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("ammonite"));
			fossilType_ = AMMONITE;
		}
		else if (typeCount == 1)
		{
			typeCount = rand() % 3;

			if (typeCount == 0)
			{
				box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("pterSkull"));
				pter_.skull = true;
			}
			else if (typeCount == 1)
			{
				box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("pterUpBody"));
				pter_.upBody = true;
			}
			else
			{
				box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("pterLowBody"));
				pter_.lowBody = true;
			}

			fossilType_ = PTER;
		}
		else if (typeCount == 2)
		{
			typeCount = rand() % 5;

			if (typeCount == 0)
			{
				box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("T-RexSkull"));
				trex_.skull = true;
			}
			else if (typeCount == 1)
			{
				box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("T-RexTorso"));
				trex_.torso = true;
			}
			else if (typeCount == 2)
			{
				box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("T-RexLeg"));
				trex_.leg = true;
			}
			else if (typeCount == 3)
			{
				box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("T-RexUpTail"));
				trex_.upTail = true;
			}
			else
			{
				box_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("T-RexLowTail"));
				trex_.lowTail = true;
			}
			fossilType_ = TREX;
		}
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
