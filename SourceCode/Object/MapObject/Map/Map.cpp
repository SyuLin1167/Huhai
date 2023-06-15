#include "Map.h"
#include"../../../Asset/Sound/Sound.h"

        // コンストラクタ //

Map::Map(int maptag)
    :ObjectBase(ObjectTag::Map)
    , mapModel(nullptr)
    , mapSound(nullptr)
    , mapTag(maptag)
{
    LoadModel();
}

        // デストラクタ //

Map::~Map()
{
    AssetManager::ReleaseMesh(objHandle);					//メッシュの削除
}

        // 読み込み処理 //

void Map::LoadModel()
{
    //モデル読み込み
    mapModel = new Model;
    mapModel->AddModel("../Assets/Map/Stage/Title.mv1");
    mapModel->AddModel("../Assets/Map/Room/Room.mv1");
    mapModel->AddModel("../Assets/Map/Stage/StageDay1.mv1");
    mapModel->AddModel("../Assets/Map/Stage/Escape.mv1");
    mapModel->AddModel("../Assets/Map/Stage/EscapeMain.mv1");
    mapModel->AddModel("../Assets/Map/Stage/GoalRoom.mv1");
    objHandle = mapModel->SetModel(mapTag);

    colModel = objHandle;																	//当たり判定モデルはモデルに
    MV1SetPosition(objHandle, objPos);														//位置セット
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));										//スケールセット

    MV1SetupCollInfo(colModel);																//当たり判定情報設定

    mapSound = new Sound;
    mapSound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor, 150);
    mapSound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);
}

        // 更新処理 //

void Map::Update(float deltaTime)
{
    if (mapTag == GOAL)
    {
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
}

        // 描画処理 //

void Map::Draw()
{
    MV1DrawModel(objHandle);
}