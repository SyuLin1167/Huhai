#include "Map.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Model/Model.h"
#include"../../../Asset/Sound/Sound.h"

// コンストラクタ //

Map::Map(int maptag)
    :ObjBase(ObjectTag::Map)
    , mapModel(nullptr)
    , mapSound(nullptr)
    , mapTag(maptag)
{
    LoadModel();
}

// デストラクタ //

Map::~Map()
{
    //メッシュ削除
    AssetManager::ReleaseMesh(objHandle);
}

        // 読み込み処理 //

void Map::LoadModel()
{
    //モデル設定
    mapModel = new Model;
    mapModel->AddModel("../Assets/Map/Stage/Title.mv1");
    mapModel->AddModel("../Assets/Map/Room/Room.mv1");
    mapModel->AddModel("../Assets/Map/Stage/StageDay1.mv1");
    mapModel->AddModel("../Assets/Map/Stage/Escape.mv1");
    mapModel->AddModel("../Assets/Map/Stage/EscapeMain.mv1");
    mapModel->AddModel("../Assets/Map/Stage/GoalRoom.mv1");
    objHandle = mapModel->GetModel(mapTag);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    //当たり判定設定
    colModel = objHandle;
    MV1SetupCollInfo(colModel);

    //サウンド設定
    mapSound = new Sound;
    mapSound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor, 150);
    mapSound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);
}

// 更新処理 //

void Map::Update(float deltaTime)
{
    //ゴール地点の処理
    if (mapTag == GOAL)
    {
        //ゴールに近づいたら表示してたどり着いたら死亡にする
        MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        if (ObjManager::GetFirstObj(ObjectTag::Player)->GetPos().x > 730)
        {
            isVisible = true;
            if (ObjManager::GetFirstObj(ObjectTag::Player)->GetPos().x > 770)
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

// 描画処理 //

void Map::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}