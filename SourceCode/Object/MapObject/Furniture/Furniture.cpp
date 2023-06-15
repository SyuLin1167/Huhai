#include "Furniture.h"

        // コンストラクタ //

Furniture::Furniture(int furtag)
    :ObjectBase(ObjectTag::Furniture)
    , furModel(nullptr)
    , furColModel(nullptr)
{
    LoadModel(furtag);
}

        // デストラクタ //

Furniture::~Furniture()
{
    AssetManager::ReleaseMesh(objHandle);					//メッシュの削除
}

        // モデル読み込み処理 //

void Furniture::LoadModel(int furtag)
{
    //---マップモデル読み込み---//
    furModel = new Model;
    furModel->AddModel("../Assets/Map/Furniture/RoomFur.mv1");
    furModel->AddModel("../Assets/Map/Furniture/StageFur.mv1");
    objHandle = furModel->SetModel(furtag);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    // 当たり判定モデル読み込み＆スケーリング＆当たり判定情報構築
    furColModel = new Model;
    furColModel->AddModel("../Assets/Map/Furniture/RoomFurCol.mv1");
    furColModel->AddModel("../Assets/Map/Furniture/StageFurCol.mv1");
    colModel = furColModel->SetModel(furtag);
    MV1SetScale(colModel, VGet(0.11f, 0.12f, 0.11f));

    // 表示モデルと当たり判定モデルの位置を微調整
    MV1SetPosition(colModel, objPos);
}

        // 更新処理 //

void Furniture::Update(float deltaTime)
{
    ColUpdate();
}

        // 描画処理 //

void Furniture::Draw()
{
    MV1DrawModel(objHandle);
}