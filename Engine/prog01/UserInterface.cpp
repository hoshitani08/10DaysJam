#include "UserInterface.h"

void UserInterface::Initialize()
{
}

void UserInterface::Finalize()
{
}

void UserInterface::Update()
{
	CompleteCalculate();
}

void UserInterface::BackDraw()
{
}

void UserInterface::NearDraw()
{
}

void UserInterface::CompleteCalculate()
{
	int count = 0;

	for (auto a : tBone_)
	{
		if (a.head && a.body && a.tail)
		{
			tBone_.erase(tBone_.begin() + count);
		}
		count++;
	}

	count = 0;

	for (auto a : sBone_)
	{
		if (a.upperBody && a.lowerBody)
		{
			sBone_.erase(sBone_.begin() + count);
		}
		count++;
	}
}

void UserInterface::TBoneScore(TParts tBone)
{
	int count = 0;

	for (auto a : tBone_)
	{
		if (!a.head && tBone.head)
		{
			a.head = tBone.head;
			break;
		}
		else if (!a.body && tBone.body)
		{
			a.body = tBone.body;
			break;
		}
		else if (!a.tail && tBone.tail)
		{
			a.tail = tBone.tail;
			break;
		}
		else if(count >= tBone_.size())
		{
			tBone_.push_back(tBone);
		}

		count++;
	}
}

void UserInterface::SBoneScore(SParts sBone)
{
	int count = 0;

	for (auto a : sBone_)
	{
		if (!a.upperBody && sBone.upperBody)
		{
			a.upperBody = sBone.upperBody;
			break;
		}
		else if (!a.lowerBody && sBone.lowerBody)
		{
			a.lowerBody = sBone.lowerBody;
			break;
		}
		else if (count >= sBone_.size())
		{
			sBone_.push_back(sBone);
		}

		count++;
	}
}
