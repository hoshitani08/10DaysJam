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
	if (!Sprite::LoadTexture(1, L"Resources/sprite/titleLogo.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(2, L"Resources/sprite/blackcurtain.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(3, L"Resources/sprite/pressA.png"))
	{
		assert(0);
	}

	// ゲーム画面
	if (!Sprite::LoadTexture(10, L"Resources/sprite/frame.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(11, L"Resources/sprite/backGroundUp.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(12, L"Resources/sprite/backGroundLow.png"))
	{
		assert(0);
	}

	if (!Sprite::LoadTexture(20, L"Resources/sprite/num/num0.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(21, L"Resources/sprite/num/num1.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(22, L"Resources/sprite/num/num2.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(23, L"Resources/sprite/num/num3.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(24, L"Resources/sprite/num/num4.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(25, L"Resources/sprite/num/num5.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(26, L"Resources/sprite/num/num6.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(27, L"Resources/sprite/num/num7.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(28, L"Resources/sprite/num/num8.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(29, L"Resources/sprite/num/num9.png"))
	{
		assert(0);
	}

	// クリア画面
	if (!Sprite::LoadTexture(30, L"Resources/sprite/Result.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(31, L"Resources/sprite/Score.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(32, L"Resources/sprite/retry.png"))
	{
		assert(0);
	}
	if (!Sprite::LoadTexture(33, L"Resources/sprite/Title.png"))
	{
		assert(0);
	}
}

SpriteFactory* SpriteFactory::GetInstance()
{
	static SpriteFactory instance;
	return &instance;
}