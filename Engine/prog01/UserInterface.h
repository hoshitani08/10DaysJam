#pragma once
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <memory>

#include "Sprite.h"

class UserInterface
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
	// �T�[�x���^�C�K�[
	struct SParts
	{
		bool upperBody = false;
		bool lowerBody = false;
	};
	// �e�B���m�T�E���X
	struct TParts
	{
		bool head = false;
		bool body = false;
		bool tail = false;
	};

public: // �����o�֐�
	// �R���X�g���N�^
	UserInterface() = default;
	// �f�X�g���N�^
	~UserInterface() = default;
	// ������
	void Initialize();
	// �I��
	void Finalize();
	// ���t���[������
	void Update();
	// ���̕`��
	void BackDraw();
	// ��O�̕`��
	void NearDraw();
	// ���΂��ꎮ�������Ƃ��̌v�Z
	void CompleteCalculate();
	// �e�B���m�T�E���X�̃X�R�A
	void TBoneScore(TParts tBone);
	// �T�[�x���^�C�K�[�̃X�R�A
	void SBoneScore(SParts sBone);
	// �X�R�A�𑫂�
	void AddScore(float score) { score_ += score; }

private: // �����o�ϐ�
	// �@��������
	float dugDistance_ = 0.0f;
	// �X�R�A
	float score_ = 0.0f;
	// �R��
	float fuel_ = 500.0f;
	//�@�T�[�x���^�C�K�[�̃p�[�c�̃f�[�^
	std::vector<SParts> sBone_;
	// �e�B���m�T�E���X�̃p�[�c�̃f�[�^
	std::vector<TParts> tBone_;
};