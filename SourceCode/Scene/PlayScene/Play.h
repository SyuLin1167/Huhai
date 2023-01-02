#pragma once
#include <DxLib.h>
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"

class CameraFps;
class Player;
class Enemy;
class Collision;
class Grid;

/* プレイシーンのクラス */
class Play :public SceneBase
{
    CameraFps* camFps = nullptr;
    Player* player = nullptr;                     //プレイヤー
    Enemy* enemy = nullptr;                       //エネミー
    Collision* col = nullptr;
    Grid* grid=nullptr;

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

};