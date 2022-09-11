#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FbxObject3d.h"
#include "Object3d.h"

class Human
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

public: // �ÓI�����o�֐�
	static std::unique_ptr<Human> Create();

public: // �����o�֐�
	// ������
	void Initialize();
	//�I��
	void Finalize();
	// ���t���[������
	void Update();
	// �`��
	void Draw();

	void Move();

	// ���W�̎擾
	const XMFLOAT3& GetPosition() { return position_; }
	// ���W�̐ݒ�
	void SetPosition(XMFLOAT3 position) { position_ = position; }
	// X,Y,Z�����̎擾
	const XMFLOAT3& GetRotation() { return rotation_; }
	// X,Y,Z�����̐ݒ�
	void SetRotation(XMFLOAT3 rotation) { rotation_ = rotation; }
	// �X�P�[���̎擾
	const XMFLOAT3& GetScale() { return scale_; }
	// �X�P�[���̐ݒ�
	void SetScale(XMFLOAT3 scale)
	{
		scale_ = scale;
		human_->SetScale(scale_);
	}

private: // �����o�ϐ�
	// ���f��
	std::unique_ptr<Object3d> human_;
	// �ʒu
	XMFLOAT3 position_ = {};
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation_ = {};
	// �X�P�[��
	XMFLOAT3 scale_ = {2,2,2};
	//
	XMFLOAT2 speed_ = { 0.1f, 0.1f };
};