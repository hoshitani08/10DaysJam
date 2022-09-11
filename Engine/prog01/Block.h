#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FbxObject3d.h"
#include "Object3d.h"

class Block
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

	typedef enum
	{
		BLANK,     // 無
		SOIL,      // 土
		ROCK,      // 岩
		COAL,      // 石炭
		IRONSTONE, // 鉄鉱石
		GOLDORE,   // 金鉱石
		FOSSIL,    // 化石


		LAVA,      // マグマ
		MAX
	} BLOCK_TYPE;

private: // 定数
	const XMFLOAT3 START_SCALE = { 2.0f, 2.0f, 2.0f };

public: // メンバ関数
	Block() = default;
	~Block() = default;
	// 初期化
	void Initialize(int type, XMFLOAT3 position);
	//終了
	void Finalize();
	// 毎フレーム処理
	void Update();
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
	// タイプの取得
	BLOCK_TYPE GetType() { return type_; }

private: // メンバ変数
	// モデル
	std::unique_ptr<Object3d> box_;
	// 位置
	XMFLOAT3 position_ = {};
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation_ = {};
	// スケール
	XMFLOAT3 scale_ = {};
	// タイプ
	BLOCK_TYPE type_;
};