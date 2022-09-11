#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FbxObject3d.h"
#include "Object3d.h"

class Human
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

public: // 静的メンバ関数
	static std::unique_ptr<Human> Create();

public: // メンバ関数
	// 初期化
	void Initialize();
	//終了
	void Finalize();
	// 毎フレーム処理
	void Update();
	// 描画
	void Draw();

	void Move();

	// 座標の取得
	const XMFLOAT3& GetPosition() { return position_; }
	// 座標の設定
	void SetPosition(XMFLOAT3 position) { position_ = position; }
	// X,Y,Z軸回りの取得
	const XMFLOAT3& GetRotation() { return rotation_; }
	// X,Y,Z軸回りの設定
	void SetRotation(XMFLOAT3 rotation) { rotation_ = rotation; }
	// スケールの取得
	const XMFLOAT3& GetScale() { return scale_; }
	// スケールの設定
	void SetScale(XMFLOAT3 scale)
	{
		scale_ = scale;
		human_->SetScale(scale_);
	}

private: // メンバ変数
	// モデル
	std::unique_ptr<Object3d> human_;
	// 位置
	XMFLOAT3 position_ = {};
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation_ = {};
	// スケール
	XMFLOAT3 scale_ = {2,2,2};
	//
	XMFLOAT2 speed_ = { 0.1f, 0.1f };
};