#include "Map.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Sound/Sound.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="maptag"></param>
Map::Map(MapTag maptag)
    :ObjBase(ObjTag::Map)
    , mapSound(new Sound)
    , mapTag(maptag)
{
    //モデル設定
    objHandle = AssetManager::GetMesh(mapFile[mapTag]);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    //当たり判定設定
    colModel = AssetManager::GetMesh(mapColFile[mapTag]);
    MV1SetPosition(colModel, objPos);
    MV1SetScale(colModel, VGet(0.11f, 0.12f, 0.11f));

    //サウンド設定
    mapSound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor);
    mapSound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
void Map::Update(const float deltaTime)
{
    //ゴール地点の処理
    if (mapTag == GOAL)
    {
        //ゴールに近づいたら表示してたどり着いたら死亡にする
        MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        if (ObjManager::GetFirstObj(ObjTag::Player)->GetPos().x > 730)
        {
            isVisible = true;
            if (ObjManager::GetFirstObj(ObjTag::Player)->GetPos().x > 770)
            {
                isAlive = false;
            }
        }
        else
        {
            isVisible = false;
        }
    }

    //当たり判定更新
    ColUpdate();
}

/// <summary>
/// 描画処理
/// </summary>
void Map::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}