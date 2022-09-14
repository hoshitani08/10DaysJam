#include "ChangeScene.h"
#include "Input.h"

ChangeScene::~ChangeScene()
{
}

ChangeScene* ChangeScene::GetInstance()
{
	static ChangeScene instance;
	return &instance;
}

void ChangeScene::Initialize()
{
	sprite_ = Sprite::Create(2, { 0.0f,0.0f }, { 1,1,1,blackCurtainAlpha_ });
	sprite_->SetSize(Input::GetInstance()->GetScreen());
}

void ChangeScene::Finalize()
{
}

void ChangeScene::Update()
{
	if (isChange_)
	{
		MoveIn();
	}
	else if (!isChange_ )
	{
		MoveOut();
	}
}

void ChangeScene::Draw()
{
	sprite_->Draw();
}

void ChangeScene::MoveIn()
{
	if (blackCurtainAlpha_ < 1.0f)
	{
		sprite_->SetColor({ 1,1,1, blackCurtainAlpha_ });
		blackCurtainAlpha_ += 0.05;
	}
	else if (blackCurtainAlpha_ > 1.0f)
	{
		isIn_ = true;
		isOut_ = false;
	}
}

void ChangeScene::MoveOut()
{
	if (blackCurtainAlpha_ > 0.0f)
	{
		sprite_->SetColor({ 1,1,1, blackCurtainAlpha_ });
		blackCurtainAlpha_ -= 0.05;
	}
	else if(blackCurtainAlpha_ < 0.0f)
	{
		isIn_ = false;
		isOut_ = true;
	}
}
