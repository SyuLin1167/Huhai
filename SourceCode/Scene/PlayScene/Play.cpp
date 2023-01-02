#include "Play.h"
#include"../../Object/Camera/CameraFps.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include"../../Map/Block/Block.h"
#include"../../Map/Map/Map.h"
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

    // ブロックを生成
    ObjManager::Entry(new Block(VGet(60, 0, 0)));
    ObjManager::Entry(new Block(VGet(70, 0, 10)));
    ObjManager::Entry(new Block(VGet(90, 0, 30)));
    ObjManager::Entry(new Block(VGet(50, 0, 10)));
    ObjManager::Entry(new Block(VGet(90, 0, 20)));

    // マップを生成
    ObjManager::Entry(new Map(VGet(0, -25, 0)));

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

    if (enemy != nullptr)                                       //インスタンスの中身が空でなければ
    {
        //---当たり判定球取得---//
        Collision::Sphere sEmy, sPly;
        sEmy = enemy->GetColSphere();               //アーチャーの当たり判定球取得
        sPly = player->GetColSphere();              //プレイヤーの当たり判定球取得

        if (col->CollisionPair(sEmy, sPly))         //球体同士の当たり判定
        {
            enemy->SetAlive(false);                 //当たっていたら死亡
            ObjManager::Release(enemy);
        }
    }

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

    grid->DrawGrid(300, 30);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Play画面:RでResultシーンへ移行");
}