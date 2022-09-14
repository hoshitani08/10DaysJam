#include "UserInterface.h"
#include "DebugText.h"
#include "Audio.h"

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

	DugCreate();
	//ScoreCreate();
	FuelCreate();
}

void UserInterface::BackDraw()
{
}

void UserInterface::NearDraw()
{
	for (int i = 0; i < dugSprite_.size(); i++)
	{
		dugSprite_[i]->Draw();
	}
	for (int i = 0; i < fuelSprite_.size(); i++)
	{
		fuelSprite_[i]->Draw();
	}
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
			Audio::GetInstance()->PlayWave(0);
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
			Audio::GetInstance()->PlayWave(0);
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

void UserInterface::DugCreate()
{
	std::array<int, 4> count;
	count[0] = dugDistance_.point / 1000;
	count[1] = (dugDistance_.point - (count[0] * 1000)) / 100;
	count[2] = (dugDistance_.point - ((count[0] * 1000) + (count[1] * 100))) / 10;
	count[3] = (dugDistance_.point - ((count[0] * 1000) + (count[1] * 100) + (count[2] * 10))) / 1
		;
	for (int i = 0; i < dugSprite_.size(); i++)
	{
		dugSprite_[i] = Sprite::Create(20 + count[i], { 0.0f,0.0f }, { 1,1,1,1 });
		dugSprite_[i]->SetPosition({ (i * 45.0f) + 920 , 100 });
		dugSprite_[i]->SetSize({ dugSprite_[i]->GetSize().x , dugSprite_[i]->GetSize().y });
	}
	
}

void UserInterface::ScoreCreate()
{
	std::array<int, 6> count;
	count[0] = score_.point / 100000;
	count[1] = (score_.point - (count[0] * 100000)) / 10000;
	count[2] = (score_.point - ((count[0] * 100000) + (count[1] * 10000))) / 1000;
	count[3] = (score_.point - ((count[0] * 100000) + (count[1] * 10000) + (count[2] * 1000))) / 100;
	count[4] = (score_.point - ((count[0] * 100000) + (count[1] * 10000) + (count[2] * 1000) + (count[3] * 100))) / 10;
	count[5] = (score_.point - ((count[0] * 100000) + (count[1] * 10000) + (count[2] * 1000) + (count[3] * 100) + (count[4] * 10))) / 1;

	for (int i = 0; i < sprite_.size(); i++)
	{
		sprite_[i] = Sprite::Create(20 + count[i], { 0.0f,0.0f }, { 1,1,1,1 });
		sprite_[i]->SetPosition({ (i * 30.0f) + 500 , 0 });
		sprite_[i]->SetSize({ sprite_[i]->GetSize().x / 2, sprite_[i]->GetSize().y / 2 });
	}
}

void UserInterface::FuelCreate()
{
	int num = fuel_.point / MAX_FUEL * 100;

	std::array<int, 3> count;
	count[0] = num / 100;
	count[1] = (num - (count[0] * 100)) / 10;
	count[2] = (num - ((count[0] * 100) + (count[1] * 10))) / 1;

	for (int i = 0; i < fuelSprite_.size(); i++)
	{
		fuelSprite_[i] = Sprite::Create(20 + count[i], { 0.0f,0.0f }, { 1,1,1,1 });
		fuelSprite_[i]->SetPosition({ (i * 45.0f) + 940 , 200 });
		fuelSprite_[i]->SetSize({ fuelSprite_[i]->GetSize().x, fuelSprite_[i]->GetSize().y });
	}
}