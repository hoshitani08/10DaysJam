#pragma once
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <algorithm>

#include "Sprite.h"

class ChangeScene final
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

private:
	ChangeScene() = default;
	~ChangeScene();

public: // �����o�֐�
	ChangeScene(const ChangeScene& r) = delete;
	ChangeScene& operator=(const ChangeScene& r) = delete;

	// �C���X�^���X����
	static ChangeScene* GetInstance();

	// ������
	void Initialize();
	//�I��
	void Finalize();
	// ���t���[������
	void Update();
	// �`��
	void Draw();

	//
	void MoveIn();
	//
	void MoveOut();

	//
	void SetIsChange(bool flag) { isChange_ = flag; }
	//
	bool GetIsChange() { return isChange_; }
	//
	void SetIsIn(bool flag) { isIn_ = flag; }
	//
	bool GetIsIn() { return isIn_; }
	//
	void SetIsOut(bool flag) { isOut_ = flag; }
	//
	bool GetIsOut() { return isOut_; }

private: // �����o�ϐ�
	//�X�v���C�g
	std::unique_ptr<Sprite> sprite_;
	// �A���t�@�l
	float blackCurtainAlpha_ = 0.0f;
	// �V�[���؂�ւ�
	bool isChange_ = false;
	//
	bool isIn_ = false;
	//
	bool isOut_ = false;
};

