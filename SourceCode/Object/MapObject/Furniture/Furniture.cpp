#include "Furniture.h"

#include"../../../Asset/AssetManager/AssetManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">:タグ</param>
Furniture::Furniture(FurName tag)
    :ObjBase(ObjTag::Furniture)
{
    Load(tag);
}

/// <summary>
/// デストラクタ
/// </summary>
Furniture::~Furniture()
{
    //処理なし
}

/// <summary>
/// 読み込み処理
/// </summary>
/// <param name="tag">:タグ</param>
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

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void Furniture::Update(float deltaTime)
{
    //当たり判定更新
    ColUpdate();
}

/// <summary>
/// 描画処理
/// </summary>
void Furniture::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}