#include "Table.h"

// @brief Tableコンストラクタ //

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
    // 表示モデルと当たり判定モデルの位置を微調整
    MV1SetPosition(colModel, objPos);

    MV1SetupCollInfo(colModel);
}

// @brief Tableデストラクタ //

Table::~Table()
{
}

// @brief Table更新処理 //

void Table::Update(float delataTime)
{
}

// @brief Table描画処理 //

void Table::Draw()
{
    MV1DrawModel(objHandle);                    //モデル描画
}