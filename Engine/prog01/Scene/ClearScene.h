#pragma once
#include "BaseScene.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include "Camera.h"

#include "Sprite.h"
#include "DebugText.h"
#include "Object3d.h"
#include "Model.h"
#include "UserInterface.h"

#include <memory>
#include <array>
#include <algorithm>

class ClearScene : public BaseScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public: // メンバ関数
	// デストラクタ
	~ClearScene();
	// 初期化
	void Initialize() override;
	//終了
	void Finalize() override;
	// 毎フレーム処理
	void Update() override;
	// 描画
	void Draw() override;
	// エフェクト描画
	void EffectDraw() override;

private: // メンバ変数
	//
	bool isSelection = true;
	bool flag = false;
	//UI
	std::unique_ptr<UserInterface> ui_;
	//スプライト
	std::array<std::unique_ptr<Sprite>, 6> sprite_;
	std::unique_ptr<Sprite> backGround_;
	std::unique_ptr<Sprite> result_;
	std::unique_ptr<Sprite> score_;
	std::unique_ptr<Sprite> retry_;
	std::unique_ptr<Sprite> title_;

	// BGMが流れているか
	bool isBgmFalg_ = false;
	//
	int audioTimer_ = 0;
	//
	float volume_ = 1.0f;
	bool maxVolume_ = false;
};