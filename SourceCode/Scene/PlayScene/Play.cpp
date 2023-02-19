#include "Play.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Enemy/Enemy.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Furniture/MapFur.h"
#include "../ResultScene/Result.h"
#include "../../Grid/Grid.h"

// @brief PlaySceneコンストラクター //

Play::Play()
    :SceneBase()
{
    BgHandle = LoadGraph("../Assets/BackGround/Play.png");

    ObjManager::Init();

    ////---カメラ生成---//
    ObjManager::Entry(new CameraFps);

    ////---プレイヤー生成---//
    ObjManager::Entry(new Player);

    ////---エネミー生成---//
    //ObjManager::Entry(new Enemy());

    ////---マップを生成---//
    ObjManager::Entry(new Map(VGet(0, 0, 0)));

    ////---家具を生成---//
    ObjManager::Entry(new MapFur(VGet(0, 0, 0)));

    ////---ドアを生成---//
    ObjManager::Entry(new Door(VGet(22, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(110, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(77, 0, 100), VGet(0, 90, 0)));

    ////---イスを生成---//
    ObjManager::Entry(new Chair(VGet(66,0,0),VGet(0,-90,0)));

    ////---照明を生成---//
    ObjManager::Entry(new Light(VGet(-10, 32, 0)));
    ObjManager::Entry(new Light(VGet(60, 32, 0),true));
    ObjManager::Entry(new Light(VGet(120, 32, 30),true));

    grid = new Grid;

}

// @brief PlaySceneデストラクター //

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


    if (CheckHitKey(KEY_INPUT_R))                               //Ｒキーが押されたら
    {
        AssetManager::ReleaseAllAsset();            //全てのアセットの開放
        ObjManager::ReleaceAllObj();                //全てのオブジェクトの開放
        return new Result();                        //リザルト画面へ
    }

    return this;                                    //常にプレイシーンを返す
}

// @brief PlayScene描画処理 //

void Play::Draw()
{
    ObjManager::Draw();
    grid->DrawGrid(300, 30);
    //DrawFormatString(0, 0, GetColor(255, 255, 255), "Play画面:RでResultシーンへ移行");
}