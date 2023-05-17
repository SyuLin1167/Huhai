#include "Model.h"
#include"../../Asset/AssetManager/AssetManager.h"

// @brief Model�ǉ�����

int Model::AddModel(string modelFileName)
{
	ModelData model = {};
	model.modelHandle = AssetManager::GetMesh(modelFileName.c_str());
	if (model.modelHandle == -1)
	{
		return-1;
	}
	modelData.emplace_back(model);

	return static_cast<int>(modelData.size()-1);
}

// @brief Model�ݒ菈�� //

int Model::SetModel(int modelId)
{
	return modelData[modelId].modelHandle;
}

// @brief ModelData�R���X�g���N�^ //

Model::ModelData::ModelData()
	:modelHandle(-1)
{
}