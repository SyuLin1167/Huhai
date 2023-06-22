#include "Table.h"

#include"../../../Asset/AssetManager/AssetManager.h"

        // コンストラクタ //

Table::Table(int objNum)
    :ObjBase(ObjectTag::Furniture)
{
    objPos = posData[objNum];
    objDir.y = dirData[objNum];

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