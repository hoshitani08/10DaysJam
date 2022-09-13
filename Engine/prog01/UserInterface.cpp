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
		if (a.skull && a.torso && a.leg && a.upTail && a.lowTail)
		{
			AddScore(7500);
			tBone_.erase(tBone_.begin() + count);
		}
		count++;
	}

	count = 0;

	for (auto a : pBone_)
	{
		if (a.skull &&  a.upBody && a.lowBody)
		{
			AddScore(5000);
			pBone_.erase(pBone_.begin() + count);
		}
		count++;
	}
}

void UserInterface::TBoneScore(Block::TParts tBone)
{
	int count = 0;

	for (auto a : tBone_)
	{
		if (!a.skull && tBone.skull)
		{
			a.skull = tBone.skull;
			break;
		}
		else if (!a.torso && tBone.torso)
		{
			a.torso = tBone.torso;
			break;
		}
		else if (!a.leg && tBone.leg)
		{
			a.leg = tBone.leg;
			break;
		}
		else if (!a.upTail && tBone.upTail)
		{
			a.upTail = tBone.upTail;
			break;
		}
		else if (!a.lowTail && tBone.lowTail)
		{
			a.lowTail = tBone.lowTail;
			break;
		}
		else if(count >= tBone_.size())
		{
			tBone_.push_back(tBone);
		}

		count++;
	}

	if (tBone_.size() == 0)
	{
		tBone_.push_back(tBone);
	}
}

void UserInterface::PBoneScore(Block::PParts pBone)
{
	int count = 0;

	for (auto a : pBone_)
	{
		if (!a.skull && pBone.skull)
		{
			a.skull = pBone.skull;
			break;
		}
		else if (!a.upBody && pBone.upBody)
		{
			a.upBody = pBone.upBody;
			break;
		}
		else if (!a.lowBody && pBone.lowBody)
		{
			a.lowBody = pBone.lowBody;
			break;
		}
		else if (count >= pBone_.size())
		{
			pBone_.push_back(pBone);
		}

		count++;
	}

	if (pBone_.size() == 0)
	{
		pBone_.push_back(pBone);
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
