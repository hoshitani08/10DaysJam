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

	struct NumberData
	{
		float savePoint = 0.0f;
		float point = 0.0f;
	};

private: // 定数
	const float MAX_FUEL = 5000;

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
	void AddScore(float score) { score_.savePoint += score; }
	// 掘った距離の計算
	void DugDistanceCalculate(float dugDistance)
	{
		dugDistance_.point += dugDistance;
		dugDistance_.savePoint += dugDistance;
	}
	// 燃料の増減
	void SetSaveFuel(float fuel) { fuel_.savePoint += fuel; }
	// 計算
	void Calculate();
	// 燃料の残量取得
	float GetFuel() { return fuel_.point; }

private: // 静的メンバ変数
	// スコア
	static NumberData score_;

private: // メンバ変数
	// 掘った距離
	NumberData dugDistance_ = {};
	// 燃料
	NumberData fuel_ = { 0.0f, 5000.0f };
	//　サーベルタイガーのパーツのデータ
	std::vector<SParts> sBone_;
	// ティラノサウルスのパーツのデータ
	std::vector<TParts> tBone_;
};