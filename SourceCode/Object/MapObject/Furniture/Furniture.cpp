#include "Furniture.h"

#include"../../../Asset/AssetManager/AssetManager.h"

Furniture::Furniture(FurName tag)
    :ObjBase(ObjTag::Furniture)
{
    Load(tag);
}

Furniture::~Furniture()
{
    //処理なし
}

void Furniture::Load(FurName tag)
{
    //モデル設定

    objHandle = AssetManager::GetMesh(furModel[tag]);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    // 当たり判定設定
    colModel = AssetManager::GetMesh(furColModel[tag]);
    MV1SetScale(colModel, VGet(0.11f, 0.12f, 0.11f));
    MV1SetPosition(colModel, objPos);
}

void Furniture::Update(const float deltaTime)
{
    //当たり判定更新
    ColUpdate();
}

void Furniture::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}