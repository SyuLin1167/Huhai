#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Table.h"

#include"../../../Asset/AssetManager/AssetManager.h"

// コンストラクタ //

Table::Table(const int objNum)
    :ObjBase(ObjectTag::Furniture)
{
    //ファイル読み込み
    LoadJsonFile("TableData.json");

    //データを読み取って座標・向きに代入
    const std::string key = std::to_string(objNum);
    auto& data = doc["data"][key.c_str()];

    objPos.x = data["pos"].GetArray()[0].GetFloat();
    objPos.y = data["pos"].GetArray()[1].GetFloat();
    objPos.z = data["pos"].GetArray()[2].GetFloat();
    objDir.y = data["dir"].GetFloat();

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Table/Table.mv1");
    MV1SetScale(objHandle, objScale);
    MV1SetPosition(objHandle, objPos);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));

    //当たり判定設定
    colModel = AssetManager::GetMesh("../Assets/Map/Table/ColTable.mv1");
    MV1SetPosition(colModel, objPos);
    MV1SetScale(colModel, VGet(0.1f, 0.1f, 0.1f));
    MV1SetRotationXYZ(colModel, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //モデルの向き設定
}

// デストラクタ //

Table::~Table()
{

}

// 更新処理 //

void Table::Update(float delataTime)
{
    //当たり判定更新
    ColUpdate();
}

// 描画処理 //

void Table::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}