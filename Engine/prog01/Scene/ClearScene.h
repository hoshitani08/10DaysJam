#pragma once
#include "BaseScene.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include "Camera.h"

#include "Sprite.h"
#include "DebugText.h"
#include "Object3d.h"
#include "Model.h"
#include "UserInterface.h"

#include <memory>
#include <array>
#include <algorithm>

class ClearScene : public BaseScene
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

public: // �����o�֐�
	// �f�X�g���N�^
	~ClearScene();
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

private: // �����o�ϐ�
	//
	bool isSelection = true;
	bool flag = false;
	//UI
	std::unique_ptr<UserInterface> ui_;
	//�X�v���C�g
	std::array<std::unique_ptr<Sprite>, 6> sprite_;
	std::unique_ptr<Sprite> backGround_;
	std::unique_ptr<Sprite> result_;
	std::unique_ptr<Sprite> score_;
	std::unique_ptr<Sprite> retry_;
	std::unique_ptr<Sprite> title_;

	// BGM������Ă��邩
	bool isBgmFalg_ = false;
	//
	int audioTimer_ = 0;
	//
	float volume_ = 1.0f;
	bool maxVolume_ = false;
};