#pragma once
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <memory>

#include "Sprite.h"

class UserInterface
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

public: // サブクラス
	// サーベルタイガー
	struct SParts
	{
		bool upperBody = false;
		bool lowerBody = false;
	};
	// ティラノサウルス
	struct TParts
	{
		bool head = false;
		bool body = false;
		bool tail = false;
	};

public: // メンバ関数
	// コンストラクタ
	UserInterface() = default;
	// デストラクタ
	~UserInterface() = default;
	// 初期化
	void Initialize();
	// 終了
	void Finalize();
	// 毎フレーム処理
	void Update();
	// 奥の描画
	void BackDraw();
	// 手前の描画
	void NearDraw();
	// 化石が一式揃ったときの計算
	void CompleteCalculate();
	// ティラノサウルスのスコア
	void TBoneScore(TParts tBone);
	// サーベルタイガーのスコア
	void SBoneScore(SParts sBone);
	// スコアを足す
	void AddScore(float score) { score_ += score; }

private: // メンバ変数
	// 掘った距離
	float dugDistance_ = 0.0f;
	// スコア
	float score_ = 0.0f;
	// 燃料
	float fuel_ = 500.0f;
	//　サーベルタイガーのパーツのデータ
	std::vector<SParts> sBone_;
	// ティラノサウルスのパーツのデータ
	std::vector<TParts> tBone_;
};