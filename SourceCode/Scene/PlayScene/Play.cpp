#include "Play.h"
#include"../../Object/Camera/CameraFps.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include"../../Map/Map/Map.h"
#include"../../Map/Door/Door.h"
#include"../../Map/Furniture/Furniture.h"
#include "../ResultScene/Result.h"
#include"../../Grid/Grid.h"

// @brief PlaySceneコンストラクター //

Play::Play()
    :SceneBase()
{
    BgHandle = LoadGraph("../SourceCode/Assets/BackGround/Play.png");

    ObjManager::Init();

    //---カメラ生成---//
    ObjManager::Entry(new CameraFps());

    //---プレイヤー生成---//
    ObjManager::Entry(new Player());

    //---エネミー生成---//
    ObjManager::Entry(new Enemy());

    //---マップを生成---//
    ObjManager::Entry(new Map(VGet(0, 0, 0)));

    //---ドアを生成---//
    ObjManager::Entry(new Door(VGet(20, 0, 0),VGet(0,0,0)));
    ObjManager::Entry(new Door(VGet(100, 0, 0),VGet(0,0,0)));
    ObjManager::Entry(new Door(VGet(0, 0, 60), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(70, 0, 90), VGet(0, 90, 0)));
    
    //---家具を生成---//
    ObjManager::Entry(new Furniture(VGet(0, 0, 0)));

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
        ObjManager::ReleaceAllObj();                //全てのオブジェクトの開放
        AssetManager::ReleaseAllAsset();            //全てのアセットの開放
        return new Result();                        //リザルト画面へ
    }

    return this;                                    //常にプレイシーンを返す
}

// @brief PlayScene描画処理 //

void Play::Draw()
{


    ObjManager::Draw();

    //grid->DrawGrid(300, 30);
    //DrawFormatString(0, 0, GetColor(255, 255, 255), "Play画面:RでResultシーンへ移行");
}