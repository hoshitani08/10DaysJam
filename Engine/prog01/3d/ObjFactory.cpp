#include "ObjFactory.h"

// �ÓI�����o�ϐ��̎���
const std::string ObjFactory::baseDirectory = "Resources/";

void ObjFactory::Initialize()
{
	LoadModel("sphere");
	LoadModel("playerDrill");
	// �y
	LoadModel("block");
	// �d����
	LoadModel("stone");
	// �ΒY
	LoadModel("sampleCoal1");
	// �S�z��
	LoadModel("sampleIron1");
	// ���z��
	LoadModel("sampleGold1");
	// �A�����i�C�g
	LoadModel("ammonite");
	// �v�e��
	LoadModel("pterSkull");
	LoadModel("pterUpBody");
	LoadModel("pterLowBody");
	// �e�B���m�T�E���X
	LoadModel("T-RexSkull");
	LoadModel("T-RexTorso");
	LoadModel("T-RexLeg");
	LoadModel("T-RexUpTail");
	LoadModel("T-RexLowTail");
	// �v���C���[
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