#include "Play.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/Ghost.h"
#include "../../Object/CharaObject/Ghost/MoveGimmic/GhostMoveGim.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/LightingLight/LitLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../ResultScene/Result.h"
#include"../Reamarks/Remarks.h"

// @brief PlaySceneコンストラクタ //

Play::Play()
    :SceneBase()
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
    ObjManager::Entry(new GhostMoveGim);


    remarks = new Remarks(TextType::Day1Stage);
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
    remarks->Update(deltaTime);
    ObjManager::Collision();

    ObjectBase* man = ObjManager::GetFirstObj(ObjectTag::Man);
    if (man)                               //Ｒキーが押されたら
    {
        if (!man->IsVisible())
        {
            AssetManager::ReleaseAllAsset();            //全てのアセットの開放
            ObjManager::ReleaseAllObj();                //全てのオブジェクトの開放
            return new Result();                        //リザルト画面へ
        }
    }

    return this;                                    //常にプレイシーンを返す
}

// @brief PlayScene描画処理 //

void Play::Draw()
{
    ObjManager::Draw();
    remarks->Draw();
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Play画面:RでResultシーンへ移行");
}