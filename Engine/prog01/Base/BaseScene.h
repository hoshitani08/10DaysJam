#pragma once

class SceneManager;

class BaseScene
{
public: // メンバ関数
	virtual ~BaseScene() = default;

	// 初期化
	virtual void Initialize() = 0;
	//終了
	virtual void Finalize() = 0;
	// 毎フレーム処理
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
	// 描画
	virtual void EffectDraw() = 0;
};