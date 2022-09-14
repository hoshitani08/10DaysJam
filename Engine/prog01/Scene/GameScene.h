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
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public: // �T�u�N���X
	struct OreData
	{
		int timer = 0;
		bool flag = false;
	};

private: // �ÓI�萔
	static const int DEBUG_TEXT_TEX_NUMBER = 0;

private: // �萔
	const XMFLOAT2 RESTRICTION_ANGLE = { 360.0f, 80.0f };
	const float START_SCALE = 1.2f;

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
	// �J�����̓���
	void CameraMove();
	// �u���b�N�̔j��
	void BlockBreak();
	// �q�b�g�{�b�N�X
	void HitBox();
	// �X�e�[�W����
	void StageCreate();
	// �z�΂̌���
	void OreBuff();
	// ���N���b�N
	void SpecialMove();
	// �v���C���[�̓���
	void PlayerMove();
	// �v���C���[�̍Ō�̓���
	void PlayerEndMove();
	//
	void BackGround();

private: // �����o�ϐ�
	//�J����
	std::unique_ptr<Camera> camera_;
	//�X�v���C�g
	std::unique_ptr<Sprite> frame_;
	std::array<std::unique_ptr<Sprite>, 3> backGround_;
	int backGroundCreateCount_ = 0;
	//�p�[�e�B�N��
	std::unique_ptr<ParticleManager> particleMan_;
	//�I�u�W�F�N�g
	std::unique_ptr<Human> player_;
	std::array<std::unique_ptr<Object3d>, 3> hit_;
	std::vector<Block*> box_;
	std::vector<Drill*> drill_;
	//UI
	std::unique_ptr<UserInterface> ui_;

	// �����������ǂ���
	bool flag = false;
	// �����̃J�E���g
	int createCount_ = 0;
	std::vector<int> createSaveCount_;
	// �i�񂾋����̃J�E���g
	int dugCount_ = 0;
	// ���z��
	OreData goldOre;
	// �S�z��
	OreData ironStone;
	// �A���O����ۑ�
	float saveAngle = 90.0f;
	// �ҋ@����
	float coolTimer = 0.0f;
	// �̌@�\��
	bool isMining = false;
	// �Ō�̏d��
	float gravity = 0.2f;
	// BGM������Ă��邩
	bool isBgmFalg_ = false;
	//
	int audioTimer_ = 0;
	//
	float volume_ = 1.5f;
	bool maxVolume_ = false;
	bool flag2 = false;

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