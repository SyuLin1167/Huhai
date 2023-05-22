#include "Play.h"

#include"../EscapeScene/Escape.h"
#include"../ResultScene/Result.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/MoveGimmic/GhostWalkGim.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/LightingLight/LitLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../UI/Reamarks/Remarks.h"

// @brief PlaySceneコンストラクタ //

Play::Play()
    :SceneBase()
    ,sceneChange(false)
{
    ////---カメラ生成---//
    ObjManager::Entry(new CameraFps);

    ////---マップを生成---//
    ObjManager::Entry(new Map(Map::MapName::STAGE));

    ////---家具を生成---//
    ObjManager::Entry(new Furniture(Furniture::FurName::Stage));

    ////---ドアを生成---//
    ObjManager::Entry(new Door(VGet(22, 0, 0), VGet(0, 180, 0)));
    ObjManager::Entry(new Door(VGet(110, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));

    ////---イスを生成---//
    ObjManager::Entry(new Chair);

    ////---照明を生成---//
    ObjManager::Entry(new NomalLight(VGet(-10, 32, 0)));
    ObjManager::Entry(new LitLight(VGet(65, 32, 0),50.0f));
    ObjManager::Entry(new LitLight(VGet(120, 32, 20),40.0f));

    ////---プレイヤー生成---//
    ObjManager::Entry(new Player);

    ////---エネミー生成---//
    ObjManager::Entry(new GhostWalkGim);

    ObjManager::Entry(new Remarks(TextType::Day1Stage));
}

// @brief PlaySceneデストラクタ //

Play::~Play()
{
    if (BgHandle != -1)
    {
        DeleteGraph(BgHandle);
    }
}

// @biref PlayScene更新処理 //

SceneBase* Play::Update(float deltaTime)
{

    ObjManager::Update(deltaTime);
    ObjManager::Collision();


    ObjectBase* man = ObjManager::GetFirstObj(ObjectTag::Man);
    if (man)                               //Ｒキーが押されたら
    {
            sceneChange = true;
    }
    else if (sceneChange)
    {
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();
        return new EscapeScene;                        //リザルト画面へ
    }

    return this;                                    //常にプレイシーンを返す
}

// @brief PlayScene描画処理 //

void Play::Draw()
{
    ObjManager::Draw();
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Stage画面:Escapeシーンへ移行");
}