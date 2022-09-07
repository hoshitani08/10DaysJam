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

#include "Human.h"

class CollisionManager;
class Player;
class ContactableObject;

class GameScene : public BaseScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private: // �ÓI�萔
	static const int DEBUG_TEXT_TEX_NUMBER = 0;

private: // �萔
	const XMFLOAT2 RESTRICTION_ANGLE = { 360.0f, 80.0f };

public: // �����o�֐�
	// �f�X�g���N�^
	~GameScene();
	// ������
	void Initialize() override;
	//�I��
	void Finalize() override;
	// ���t���[������
	void Update() override;
	// �`��
	void Draw() override;
	// �G�t�F�N�g�`��
	void EffectDraw() override;

	// �u���b�N����
	void BlockCreate(std::string fName);

private: // �����o�ϐ�
	//�J����
	std::unique_ptr<Camera> camera_;
	//�X�v���C�g
	std::unique_ptr<Sprite> sprite_;
	//�p�[�e�B�N��
	std::unique_ptr<ParticleManager> particleMan_;
	//�I�u�W�F�N�g
	std::unique_ptr<Human> player_;
	std::unique_ptr<Object3d> hit_;
	std::vector<Object3d*> box_ = {};

	// �����������ǂ���
	bool flag = false;

	//���C�g
	std::unique_ptr<LightGroup> light_;
	//�������������l
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	float fighterPos[3] = { 1, 0.0f, 0 };
	//�����蔻��
	CollisionManager* collisionManager_ = nullptr;
};