#include "SpriteFactory.h"

void SpriteFactory::Initialize()
{
	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(0, L"Resources/debugfont.png"))
	{
		assert(0);
	}
	// デバッグテキスト初期化
	DebugText::GetInstance()->Initialize(0);

	// テクスチャ読み込み
}

SpriteFactory* SpriteFactory::GetInstance()
{
	static SpriteFactory instance;
	return &instance;
}