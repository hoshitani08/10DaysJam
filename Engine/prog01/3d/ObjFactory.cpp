#include "ObjFactory.h"

// 静的メンバ変数の実体
const std::string ObjFactory::baseDirectory = "Resources/";

void ObjFactory::Initialize()
{
	LoadModel("sphere");
	LoadModel("playerDrill");
	// 土
	LoadModel("block");
	// 硬い石
	LoadModel("stone");
	// 石炭
	LoadModel("sampleCoal1");
	// 鉄鉱石
	LoadModel("sampleIron1");
	// 金鉱石
	LoadModel("sampleGold1");
	// アンモナイト
	LoadModel("ammonite");
	// プテラ
	LoadModel("pterSkull");
	LoadModel("pterUpBody");
	LoadModel("pterLowBody");
	// ティラノサウルス
	LoadModel("T-RexSkull");
	LoadModel("T-RexTorso");
	LoadModel("T-RexLeg");
	LoadModel("T-RexUpTail");
	LoadModel("T-RexLowTail");
	// プレイヤー
	LoadModel("player");
}

void ObjFactory::Finalize()
{
	for (auto& a : modelData)
	{
		a.model.reset();
		a.fName.clear();
	}
}

void ObjFactory::LoadModel(std::string fName, bool smoothing)
{
	ModelData tempData;
	tempData.fName = baseDirectory + fName + ".obj";
	tempData.model = Model::CreateFromObject(fName, smoothing);

	modelData.push_back(std::move(tempData));
}

Model* ObjFactory::GetModel(std::string fName)
{
	for (int i = 0; i < modelData.size(); i++)
	{
		if (modelData[i].fName == baseDirectory + fName + ".obj")
		{
			return modelData[i].model.get();
		}
	}

	return nullptr;
}

ObjFactory* ObjFactory::GetInstance()
{
	static ObjFactory instance;
	return &instance;
}