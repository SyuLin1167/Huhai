#include "Play.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Object/Camera/CameraFps.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../ResultScene/Result.h"
#include"../../Grid/Grid.h"

// @brief PlaySceneコンストラクター //

Play::Play()
    :SceneBase()
{
    BgHandle = LoadGraph("../SourceCode/Assets/BackGround/Play.png");

    ObjManager::Init();

    camFps = new CameraFps();
    ObjManager::Entry(camFps);

    player = new Player();
    ObjManager::Entry(player);

    enemy = new Enemy();
    ObjManager::Entry(enemy);

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


    if (enemy != nullptr)                                              //インスタンスの中身が空でなければ
    {
        //---当たり判定球取得---//
        Sphere sEmy, sPly;
        sEmy = enemy->GetColSphere();                                  //アーチャーの当たり判定球取得
        sPly = player->GetColSphere();                                    //プレイヤーの当たり判定球取得

        if (CollisionPair(sEmy, sPly))                      //球体同士の当たり判定
        {
            enemy->SetAlive(false);                                //当たっていたら死亡
        }
    }

    if (CheckHitKey(KEY_INPUT_R))
    {
        ObjManager::ReleaceAllObj();
        AssetManager::ReleaseAllAsset();
        return new Result();

    }
    return this;
}

// @brief PlayScene描画処理 //

void Play::Draw()
{


    ObjManager::Draw();

    grid->DrawGrid(300, 30);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Play画面:RでResultシーンへ移行");
}