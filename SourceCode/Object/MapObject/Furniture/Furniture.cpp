#include "Furniture.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Model/Model.h"

// コンストラクタ //

Furniture::Furniture(int tag)
    :ObjBase(ObjectTag::Furniture)
    , furModel(nullptr)
    , furColModel(nullptr)
{
    Load(tag);
}

// デストラクタ //

Furniture::~Furniture()
{
    //モデル削除
    AssetManager::ReleaseMesh(objHandle);
}

// 読み込み処理 //

void Furniture::Load(int tag)
{
    //モデル設定
    furModel = new Model;
    furModel->AddModel("../Assets/Map/Furniture/RoomFur.mv1");
    furModel->AddModel("../Assets/Map/Furniture/StageFur.mv1");
    objHandle = furModel->GetModel(tag);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    // 当たり判定設定
    furColModel = new Model;
    furColModel->AddModel("../Assets/Map/Furniture/RoomFurCol.mv1");
    furColModel->AddModel("../Assets/Map/Furniture/StageFurCol.mv1");
    colModel = furColModel->GetModel(tag);
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