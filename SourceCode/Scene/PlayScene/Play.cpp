#include "Play.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../ResultScene/Result.h"

// @brief PlaySceneコンストラクター //

Play::Play()
    :SceneBase()
    , cPos(VGet(0.0f, 40.0f, -70.0f))
    , cTarget(VGet(0.0f, 0.0f, 0.0f))
{
    BgHandle = LoadGraph("../SourceCode/Assets/BackGround/Play.png");

    SetCameraNearFar(CameraNear, CameraFar);                      //カメラの描画範囲設定
    SetCameraPositionAndTarget_UpVecY(cPos, cTarget);   //視点からターゲットを見る角度にカメラ設置

    ObjManager::Init();

    player = new Player();
    ObjManager::Entry(player);

    enemy = new Enemy();
    ObjManager::Entry(enemy);
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
        return new Result();
    }
    return this;
}

// @brief PlayScene描画処理 //

void Play::Draw()
{
    //---地面グリッドを描画---//(のちにゲームオブジェクトに移行)
    for (int ix = 0; ix < DivideNum + 1; ix++)
    {
        p1 = VGet(ix * GridSpace - GridAllSize * 0.5f, 0.0f, -GridAllSize * 0.5f);
        p2 = VGet(ix * GridSpace - GridAllSize * 0.5f, 0.0f, GridAllSize * 0.5f);

        DrawLine3D(p1, p2, GetColor(0, 255, 0));
    }
    for (int iy = 0; iy < DivideNum + 1; iy++)
    {
        p1 = VGet(-GridAllSize * 0.5f, 0.0f, iy * GridSpace - GridAllSize * 0.5f);
        p2 = VGet(GridAllSize * 0.5f, 0.0f, iy * GridSpace - GridAllSize * 0.5f);

        DrawLine3D(p1, p2, GetColor(0, 255, 0));
    }//描画終わり


    ObjManager::Draw();

    DrawFormatString(0, 0, GetColor(255, 255, 255), "Play画面:RでResultシーンへ移行");
}