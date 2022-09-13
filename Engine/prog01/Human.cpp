#include "Human.h"
#include "FbxFactory.h"
#include "ObjFactory.h"

#include "DirectXCommon.h"
#include "Input.h"
#include "Vector.h"
#include "Collision.h"

#include "DebugText.h"

std::unique_ptr<Human> Human::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Human* human = new Human();
	if (human == nullptr)
	{
		return nullptr;
	}
	human->Initialize();

	return std::unique_ptr<Human>(human);
}

void Human::Initialize()
{
	human_ = Object3d::Create(ObjFactory::GetInstance()->GetModel("samplePlayer"));
	human_->SetPosition({ 0,3,0 });
	human_->SetRotation({ 0,90,0 });
	human_->SetScale(scale_);
}

void Human::Finalize()
{
}

void Human::Update()
{
	human_->Update();
}

void Human::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();

	human_->Draw();
}

void Human::Move(float angle, XMFLOAT2 gradient, float gravity)
{
	Input* input = Input::GetInstance();

	position_ = human_->GetPosition();

	float hSpeed = (float)sqrtf((gradient.x * gradient.x) + (gradient.y * gradient.y));
	float vector = sinf((angle * 3.14) / 180.0f) * hSpeed * 1.5f;
	gravity_ += gravity;

	if (gravity_ >= 0.6f)
	{
		gravity_ = 0.6f;
	}

	position_.x += vector;
	position_.y -= gravity_;

	if (position_.x < -30)
	{
		position_.x = -30;
	}
	else if (position_.x > 26)
	{
		position_.x = 26;
	}

	human_->SetPosition(position_);
}

void Human::EndMove(float gravity)
{
	position_.y -= gravity;

	human_->SetPosition(position_);
}

void Human::HitBox(Block* box)
{
	Box enemy;
	enemy.center = { box->GetPosition().x, box->GetPosition().y, box->GetPosition().z, 0 };
	enemy.scale = { box->GetScale().x * 1.2f, box->GetScale().x * 1.2f, box->GetScale().x * 1.2f };

	Sphere player[3];
	player[0].center = { human_->GetPosition().x - 1.2f, human_->GetPosition().y    , human_->GetPosition().z, 0 };
	player[0].radius = 1;
	player[1].center = { human_->GetPosition().x + 1.2f, human_->GetPosition().y    , human_->GetPosition().z, 0 };
	player[1].radius = 1;
	player[2].center = { human_->GetPosition().x    , human_->GetPosition().y - 1, human_->GetPosition().z, 0 };
	player[2].radius = 1;

	XMFLOAT3 position = human_->GetPosition();

	for (int i = 0; i < _countof(player); i++)
	{
		if (box->GetBlockType() == Block::SOIL && Collision::CheckSphere2Box(player[i], enemy))
		{
			if (i == 0)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x + box->GetScale().x) + human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 1)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x - box->GetScale().x) - human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 2 && human_->GetScale().y >= box->GetPosition().y + box->GetScale().y)
			{
				XMFLOAT3 pos =
				{
					box->GetPosition().x,
					(box->GetPosition().y + box->GetScale().y) + human_->GetScale().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}

			gravity_ = 0.0f;
		}
		else if (box->GetBlockType() == Block::ROCK && Collision::CheckSphere2Box(player[i], enemy))
		{
			if (i == 0)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x + box->GetScale().x) + human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 1)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x - box->GetScale().x) - human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 2 && human_->GetScale().y >= box->GetPosition().y + box->GetScale().y)
			{
				XMFLOAT3 pos =
				{
					box->GetPosition().x,
					(box->GetPosition().y + box->GetScale().y) + human_->GetScale().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}

			gravity_ = 0.0f;
		}
		else if (box->GetBlockType() == Block::COAL && Collision::CheckSphere2Box(player[i], enemy))
		{
			if (i == 0)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x + box->GetScale().x) + human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 1)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x - box->GetScale().x) - human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 2 && human_->GetScale().y >= box->GetPosition().y + box->GetScale().y)
			{
				XMFLOAT3 pos =
				{
					box->GetPosition().x,
					(box->GetPosition().y + box->GetScale().y) + human_->GetScale().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}

			gravity_ = 0.0f;
		}
		else if (box->GetBlockType() == Block::IRONSTONE && Collision::CheckSphere2Box(player[i], enemy))
		{
			if (i == 0)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x + box->GetScale().x) + human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 1)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x - box->GetScale().x) - human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 2 && human_->GetScale().y >= box->GetPosition().y + box->GetScale().y)
			{
				XMFLOAT3 pos =
				{
					box->GetPosition().x,
					(box->GetPosition().y + box->GetScale().y) + human_->GetScale().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}

			gravity_ = 0.0f;
		}
		else if (box->GetBlockType() == Block::GOLDORE && Collision::CheckSphere2Box(player[i], enemy))
		{
			if (i == 0)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x + box->GetScale().x) + human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 1)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x - box->GetScale().x) - human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 2 && human_->GetScale().y >= box->GetPosition().y + box->GetScale().y)
			{
				XMFLOAT3 pos =
				{
					box->GetPosition().x,
					(box->GetPosition().y + box->GetScale().y) + human_->GetScale().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}

			gravity_ = 0.0f;
		}
		else if (box->GetBlockType() == Block::FOSSIL && Collision::CheckSphere2Box(player[i], enemy))
		{
			if (i == 0)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x + box->GetScale().x) + human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 1)
			{
				XMFLOAT3 pos =
				{
					(box->GetPosition().x - box->GetScale().x) - human_->GetScale().x,
					box->GetPosition().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}
			else if (i == 2 && human_->GetScale().y >= box->GetPosition().y + box->GetScale().y)
			{
				XMFLOAT3 pos =
				{
					box->GetPosition().x,
					(box->GetPosition().y + box->GetScale().y) + human_->GetScale().y,
					box->GetPosition().z
				};

				human_->SetPosition(pos);
			}

			gravity_ = 0.0f;
		}
	}
}

void Human::SetPosition(XMFLOAT3 position)
{
	position_ = position;
	human_->SetPosition(position_);
}

void Human::SetRotation(XMFLOAT3 rotation)
{
	rotation_ = rotation;
	human_->SetRotation(rotation_);
}

void Human::SetScale(XMFLOAT3 scale)
{
	scale_ = scale;
	human_->SetScale(scale_);
}
