#pragma once
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <algorithm>

#include "Sprite.h"

class ChangeScene final
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

private:
	ChangeScene() = default;
	~ChangeScene();

public: // メンバ関数
	ChangeScene(const ChangeScene& r) = delete;
	ChangeScene& operator=(const ChangeScene& r) = delete;

	// インスタンス生成
	static ChangeScene* GetInstance();

	// 初期化
	void Initialize();
	//終了
	void Finalize();
	// 毎フレーム処理
	void Update();
	// 描画
	void Draw();

	//
	void MoveIn();
	//
	void MoveOut();

	//
	void SetIsChange(bool flag) { isChange_ = flag; }
	//
	bool GetIsChange() { return isChange_; }
	//
	void SetIsIn(bool flag) { isIn_ = flag; }
	//
	bool GetIsIn() { return isIn_; }
	//
	void SetIsOut(bool flag) { isOut_ = flag; }
	//
	bool GetIsOut() { return isOut_; }

private: // メンバ変数
	//スプライト
	std::unique_ptr<Sprite> sprite_;
	// アルファ値
	float blackCurtainAlpha_ = 0.0f;
	// シーン切り替え
	bool isChange_ = false;
	//
	bool isIn_ = false;
	//
	bool isOut_ = false;
};

