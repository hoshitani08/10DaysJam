#include "UserInterface.h"
#include "DebugText.h"

UserInterface::NumberData UserInterface::score_ = {};

void UserInterface::Initialize()
{
}

void UserInterface::Finalize()
{
}

void UserInterface::Update()
{
	Calculate();
	DebugText::GetInstance()->VariablePrint(0, 0, "dugDistance_", dugDistance_.point, 1.0f);
	DebugText::GetInstance()->VariablePrint(0, 16, "score_", score_.point, 1.0f);
	DebugText::GetInstance()->VariablePrint(0, 32, "fuel_", fuel_.point, 1.0f);
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
			AddScore(7500);
			tBone_.erase(tBone_.begin() + count);
		}
		count++;
	}

	count = 0;

	for (auto a : sBone_)
	{
		if (a.upperBody && a.lowerBody)
		{
			AddScore(5000);
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

void UserInterface::Calculate()
{
	if (score_.savePoint > 0)
	{
		score_.point += 1;
		score_.savePoint--;
	}

	if (dugDistance_.savePoint > 0)
	{
		score_.point += dugDistance_.savePoint;
		dugDistance_.savePoint--;
	}

	if (fuel_.savePoint > 0)
	{
		fuel_.point += 1;
		fuel_.savePoint--;

		if (fuel_.point >= MAX_FUEL)
		{
			fuel_.point = MAX_FUEL;
			fuel_.savePoint = 0;
		}
	}
	else if(fuel_.savePoint < 0)
	{
		fuel_.point -= 1;
		fuel_.savePoint++;

		if (fuel_.point <= 0)
		{
			fuel_.point = 0;
		}
	}
}
