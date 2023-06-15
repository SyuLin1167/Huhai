#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"

/* PlaySceneクラス */
class Play :public SceneBase
{

public:
    /// <summary>
    /// PlaySceneコンストラクタ
    /// </summary>
    Play();

    /// <summary>
    /// PlaySceneデストラクタ
    /// </summary>
    ~Play();

    /// <summary>
    /// PlayScene更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>現在のシーンのポインタ</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// PlaySceneの描画
    /// </summary>
    void Draw()override;

private:
    bool sceneChange;
};