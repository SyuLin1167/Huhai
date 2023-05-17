#include "Model.h"
#include"../../Asset/AssetManager/AssetManager.h"

// @brief Model追加処理

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

// @brief Model設定処理 //

int Model::SetModel(int modelId)
{
	return modelData[modelId].modelHandle;
}

// @brief ModelDataコンストラクタ //

Model::ModelData::ModelData()
	:modelHandle(-1)
{
}