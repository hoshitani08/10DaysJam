#pragma once
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <memory>

#include "Sprite.h"
#include "Block.h"

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
	struct NumberData
	{
		float savePoint = 0.0f;
		float point = 0.0f;
		float all = 0.0f;
	};

private: // �萔
	const float MAX_FUEL = 2000;

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
	void TBoneScore(Block::TParts tBone);
	// �v�e���̃X�R�A
	void PBoneScore(Block::PParts pBone);
	// �X�R�A�𑫂�
	void AddScore(float score)
	{
		score_.savePoint += score;
		score_.all += score;
	}
	// �@���������̌v�Z
	void DugDistanceCalculate(float dugDistance)
	{
		dugDistance_.point += dugDistance;
		dugDistance_.savePoint += dugDistance;
	}
	// �R���̑���
	void SetSaveFuel(float fuel) { fuel_.savePoint += fuel; }
	// �v�Z
	void Calculate();
	// �R���̎c�ʎ擾
	float GetFuel() { return fuel_.point; }

	float GetScore() { return score_.all; }

private: // �ÓI�����o�ϐ�
	// �X�R�A
	static NumberData score_;

private: // �����o�ϐ�
	// �@��������
	NumberData dugDistance_ = {};
	// �R��
	NumberData fuel_ = { 0.0f, MAX_FUEL };
	//�@�T�[�x���^�C�K�[�̃p�[�c�̃f�[�^
	std::vector<Block::PParts> pBone_;
	// �e�B���m�T�E���X�̃p�[�c�̃f�[�^
	std::vector<Block::TParts> tBone_;
};