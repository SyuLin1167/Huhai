#include "Table.h"

        // コンストラクタ //

Table::Table(int objNum)
    :ObjectBase(ObjectTag::Furniture)
{
    objPos = posData[objNum];
    objDir.y = dirData[objNum];
    objHandle = AssetManager::GetMesh("../Assets/Map/Table/Table.mv1");
    MV1SetScale(objHandle, objScale);                                                       //モデルのサイズ設定
    MV1SetPosition(objHandle, objPos);                                                      //モデルの座標設定
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //モデルの向き設定

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
    ColUpdate();
}

        // 描画処理 //

void Table::Draw()
{
    MV1DrawModel(objHandle);                    //モデル描画
}