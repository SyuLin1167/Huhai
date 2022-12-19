#pragma once
#include <DxLib.h>
#include"../SceneBase/SceneBase.h"

const float CameraNear = 1.0f;       //カメラの描画範囲(近)
const float CameraFar = 2000.0f;     //カメラの描画範囲(遠)

class Player;
class Enemy;

/* プレイシーンのクラス */
class Play :public SceneBase
{
    Player* player = nullptr;                     //プレイヤー
    Enemy* enemy = nullptr;                       //エネミー

public:
    /// <summary>
    /// コンストラクター
    /// </summary>
    Play();

    /// <summary>
    /// デストラクター
    /// </summary>
    ~Play();

    /// <summary>
    /// PlayScene更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>現在のシーンのポインタ</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// プレイシーンの描画
    /// </summary>
    void Draw()override;

private:
    //---地面グリッド描画関連---//(のちにゲームオブジェクトに移行)
    VECTOR p1;
    VECTOR p2;
    const float GridAllSize = 100.0f;
    const int DivideNum = 10;
    const float GridSpace = GridAllSize / DivideNum;
};