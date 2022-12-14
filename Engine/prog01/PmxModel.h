#pragma once
#include <DirectXMath.h>
#include <vector>
#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include <unordered_map>
#include <memory>

#include "PmxMesh.h"

using namespace DirectX;

class PmxModel
{
public:
	//フレンドクラス
	friend class PmxLoader;

private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
	// std::を省略
	using string = std::string;
	using wstring = std::wstring;

private: // 定数
	static constexpr int NO_DATA_FLAG = -1;

public: // サブクラス
	struct Vertex
	{
		// 頂点座標
		XMFLOAT3 position;
		// 法線
		XMFLOAT3 normal;
		// UV座標
		XMFLOAT2 uv;
		// 追加UV座標
		std::vector<XMFLOAT4> additionalUV;

		// ボーンウェイト
		struct Weight
		{
			enum Type
			{
				BDEF1,
				BDEF2,
				BDEF4,
				SDEF,
			};

			Type type;
			int born1;
			int	born2;
			int	born3;
			int	born4;
			float weight1;
			float weight2;
			float weight3;
			float weight4;
			XMFLOAT3 c;
			XMFLOAT3 r0;
			XMFLOAT3 r1;
		} weight;

		// エッジ倍率
		float edgeMagnif;
	};

	struct Surface
	{
		int vertexIndex;
	};

	struct Material
	{
		XMFLOAT4 diffuse;
		XMFLOAT3 specular;
		float specularity;
		XMFLOAT3 ambient;

		int colorMapTextureIndex;
		int toonTextureIndex;
		// (スフィアテクスチャは非対応)

		// 材質ごとの頂点数
		int vertexNum;
	};

	struct Bone
	{
		// ボーン名
		std::wstring name;
		// English version
		std::string nameEnglish;
		XMFLOAT3 position;
		int parentIndex;
		int transformationLevel;
		unsigned short flag;
		XMFLOAT3 coordOffset;
		int childrenIndex;
		int impartParentIndex;
		float impartRate;
		// 固定軸方向ベクトル
		XMFLOAT3 fixedAxis;
		// ローカルのX軸方向ベクトル
		XMFLOAT3 localAxisX;
		// ローカルのZ軸方向ベクトル
		XMFLOAT3 localAxisZ;
		int externalParentKey;
		int ikTargetIndex;
		int ikLoopCount;
		float ikUnitAngle;
		struct IKLink
		{
			int index;
			bool existAngleLimited;
			XMFLOAT3 limitAngleMin;
			XMFLOAT3 limitAngleMax;
		};
		std::vector<IKLink> ikLinks;
	};

	// メッシュ
	struct Mesh
	{
		unsigned vertexNum;
		ComPtr<ID3D12Resource> texbuff;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 specularColor;
		float specularity;
		XMFLOAT3 ambientColor;
	};

public:
	inline size_t getMeshesSize() { return meshes.size(); }
	//inline bool meshHasTexture(int _meshIndex) { return meshes[_meshIndex]->GetpTexture(); }
	bool Initialize();
	void Draw(ID3D12GraphicsCommandList* cmdList);

	// 静的初期化
	static void StaticInitialize(ID3D12Device* device);

	static std::unique_ptr<PmxModel> CreateFromObject(const std::wstring& text, bool smoothing = false);

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;

private:
	//unsigned mIndexCount;
	std::vector<Mesh> meshes;

private: //FBXから必要だと思って引っ張ってきたもの
	//頂点データ配列
	std::vector<Vertex> vertices;
	std::vector<Surface> surfaces;
	std::vector<wstring> texturePaths;
	std::vector<Material> materials;
	std::vector<Bone> bones;
	//頂点インデックス配列
	std::vector<unsigned short> indices;
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//SRVのGPUハンドル
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle;
};