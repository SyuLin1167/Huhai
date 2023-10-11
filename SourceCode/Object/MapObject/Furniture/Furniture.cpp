#include "Furniture.h"

#include"../../../Asset/AssetManager/AssetManager.h"

// コンストラクタ //

Furniture::Furniture(FurName tag)
    :ObjBase(ObjTag::Furniture)
{
    Load(tag);
}

// デストラクタ //

Furniture::~Furniture()
{
}

// 読み込み処理 //

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

// 更新処理 //

void Furniture::Update(float deltaTime)
{
    //当たり判定更新
    ColUpdate();
}

// 描画処理 //

void Furniture::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}