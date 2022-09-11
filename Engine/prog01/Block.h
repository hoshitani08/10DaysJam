#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FbxObject3d.h"
#include "Object3d.h"

class Block
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

	typedef enum
	{
		BLANK,     // ��
		SOIL,      // �y
		ROCK,      // ��
		COAL,      // �ΒY
		IRONSTONE, // �S�z��
		GOLDORE,   // ���z��
		FOSSIL,    // ����


		LAVA,      // �}�O�}
		MAX
	} BLOCK_TYPE;

private: // �萔
	const XMFLOAT3 START_SCALE = { 2.0f, 2.0f, 2.0f };

public: // �����o�֐�
	Block() = default;
	~Block() = default;
	// ������
	void Initialize(int type, XMFLOAT3 position);
	//�I��
	void Finalize();
	// ���t���[������
	void Update();
	// �`��
	void Draw();

	// ���W�̎擾
	const XMFLOAT3& GetPosition() { return position_; }
	// ���W�̐ݒ�
	void SetPosition(XMFLOAT3 position);
	// X,Y,Z�����̎擾
	const XMFLOAT3& GetRotation() { return rotation_; }
	// X,Y,Z�����̐ݒ�
	void SetRotation(XMFLOAT3 rotation);
	// �X�P�[���̎擾
	const XMFLOAT3& GetScale() { return scale_; }
	// �X�P�[���̐ݒ�
	void SetScale(XMFLOAT3 scale);
	// �^�C�v�̎擾
	BLOCK_TYPE GetType() { return type_; }

private: // �����o�ϐ�
	// ���f��
	std::unique_ptr<Object3d> box_;
	// �ʒu
	XMFLOAT3 position_ = {};
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation_ = {};
	// �X�P�[��
	XMFLOAT3 scale_ = {};
	// �^�C�v
	BLOCK_TYPE type_;
};