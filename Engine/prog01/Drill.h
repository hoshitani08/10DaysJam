#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FbxObject3d.h"
#include "Object3d.h"

class Drill
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

private: // 定数
	const XMFLOAT3 START_SCALE = { 2.0f, 2.0f, 2.0f };

public: // メンバ関数
	Drill() = default;
	~Drill() = default;
	// 初期化
	void Initialize(XMFLOAT3 hPosition, XMFLOAT3 pPosition, float saveAngle);
	//終了
	void Finalize();
	// 毎フレーム処理
	void Update(XMFLOAT3 pPosition);
	// 描画
	void Draw();

	// 座標の取得
	const XMFLOAT3& GetPosition() { return position_; }
	// 座標の設定
	void SetPosition(XMFLOAT3 position);
	// X,Y,Z軸回りの取得
	const XMFLOAT3& GetRotation() { return rotation_; }
	// X,Y,Z軸回りの設定
	void SetRotation(XMFLOAT3 rotation);
	// スケールの取得
	const XMFLOAT3& GetScale() { return scale_; }
	// スケールの設定
	void SetScale(XMFLOAT3 scale);

	// 破壊した数を足す
	void AddCount(float count) { count_ += count; }
	// フラグの取得
	bool GetFlag() { return flag_; }

private: // メンバ変数
	// モデル
	std::unique_ptr<Object3d> object_;
	// 位置
	XMFLOAT3 position_ = {};
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation_ = {};
	// スケール
	XMFLOAT3 scale_ = {};
	// 速さ
	XMFLOAT2 speed_ = {};
	// ブロックをどれだけ壊したか
	int count_ = 0;
	// 消すかどうか
	bool flag_ = false;
};

