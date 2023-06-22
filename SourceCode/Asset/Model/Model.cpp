#include "Model.h"
#include"../../Asset/AssetManager/AssetManager.h"


// コンストラクタ //

Model::Model()
{
}

// デストラクタ //

Model::~Model()
{
    //データ削除
    while (modelData.size() == 0)
    {
        modelData.pop_back();
    }
}

// 追加処理 //

int Model::AddModel(std::string modelFileName)
{
    //メッシュを登録&取得する
    ModelData model = {};
    model.modelHandle = AssetManager::GetMesh(modelFileName.c_str());

    //中身が空だったらそのまま返す
    if (model.modelHandle == -1)
	{
        return model.modelHandle;
    }

    //データに追加してIDを返す
    modelData.emplace_back(model);
    return static_cast<int>(modelData.size() - 1);
}

// 設定処理 //

int Model::GetModel(int modelID)
{
    //データ内のIDのモデルハンドルを返す
	return modelData[modelID].modelHandle;
}

// コンストラクタ //

Model::ModelData::ModelData()
	:modelHandle(-1)
{
}