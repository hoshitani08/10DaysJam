#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FbxObject3d.h"
#include "Object3d.h"

class Drill
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

private: // �萔
	const XMFLOAT3 START_SCALE = { 2.0f, 2.0f, 2.0f };

public: // �����o�֐�
	Drill() = default;
	~Drill() = default;
	// ������
	void Initialize(XMFLOAT3 hPosition, XMFLOAT3 pPosition, float saveAngle);
	//�I��
	void Finalize();
	// ���t���[������
	void Update(XMFLOAT3 pPosition);
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

	// �j�󂵂����𑫂�
	void AddCount(float count) { count_ += count; }
	// �t���O�̎擾
	bool GetFlag() { return flag_; }

private: // �����o�ϐ�
	// ���f��
	std::unique_ptr<Object3d> object_;
	// �ʒu
	XMFLOAT3 position_ = {};
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation_ = {};
	// �X�P�[��
	XMFLOAT3 scale_ = {};
	// ����
	XMFLOAT2 speed_ = {};
	// �u���b�N���ǂꂾ���󂵂���
	int count_ = 0;
	// �������ǂ���
	bool flag_ = false;
};

