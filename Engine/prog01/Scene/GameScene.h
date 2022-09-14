#pragma once

#include "BaseScene.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "ParticleManager.h"
#include "ParticleEmitter.h"
#include "CollisionPrimitive.h"
#include "Camera.h"
#include "LightGroup.h"
#include "FbxObject3d.h"

#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <algorithm>

#include "Human.h"
#include "Block.h"
#include "Drill.h"
#include "UserInterface.h"

class CollisionManager;
class Player;
class ContactableObject;

class GameScene : public BaseScene
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
	struct OreData
	{
		int timer = 0;
		bool flag = false;
	};

private: // 静的定数
	static const int DEBUG_TEXT_TEX_NUMBER = 0;

private: // 定数
	const XMFLOAT2 RESTRICTION_ANGLE = { 360.0f, 80.0f };
	const float START_SCALE = 1.2f;

public: // メンバ関数
	// デストラクタ
	~GameScene();
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

	// ブロック生成
	void BlockCreate(std::string fName);
	// カメラの動き
	void CameraMove();
	// ブロックの破壊
	void BlockBreak();
	// ヒットボックス
	void HitBox();
	// ステージ生成
	void StageCreate();
	// 鉱石の効果
	void OreBuff();
	// 左クリック
	void SpecialMove();
	// プレイヤーの動き
	void PlayerMove();
	// プレイヤーの最後の動き
	void PlayerEndMove();
	//
	void BackGround();

private: // メンバ変数
	//カメラ
	std::unique_ptr<Camera> camera_;
	//スプライト
	std::unique_ptr<Sprite> frame_;
	std::array<std::unique_ptr<Sprite>, 3> backGround_;
	int backGroundCreateCount_ = 0;
	//パーティクル
	std::unique_ptr<ParticleManager> particleMan_;
	//オブジェクト
	std::unique_ptr<Human> player_;
	std::array<std::unique_ptr<Object3d>, 3> hit_;
	std::vector<Block*> box_;
	std::vector<Drill*> drill_;
	//UI
	std::unique_ptr<UserInterface> ui_;

	// 当たったかどうか
	bool flag = false;
	// 生成のカウント
	int createCount_ = 0;
	std::vector<int> createSaveCount_;
	// 進んだ距離のカウント
	int dugCount_ = 0;
	// 金鉱石
	OreData goldOre;
	// 鉄鉱石
	OreData ironStone;
	// アングルを保存
	float saveAngle = 90.0f;
	// 待機時間
	float coolTimer = 0.0f;
	// 採掘可能か
	bool isMining = false;
	// 最後の重力
	float gravity = 0.2f;
	// BGMが流れているか
	bool isBgmFalg_ = false;
	//
	int audioTimer_ = 0;
	//
	float volume_ = 1.5f;
	bool maxVolume_ = false;
	bool flag2 = false;

	//ライト
	std::unique_ptr<LightGroup> light_;
	//光線方向初期値
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	float fighterPos[3] = { 1, 0.0f, 0 };
	//当たり判定
	CollisionManager* collisionManager_ = nullptr;
};