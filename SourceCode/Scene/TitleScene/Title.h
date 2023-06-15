#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"
#include"../../BlendMode/BlendMode.h"
#include"../../UI/Select/SelectType.h"


    /* TitleSceneクラス */
class Title :public SceneBase
{
    class Door* door = nullptr;
    class BlendMode* titleBlend;
    class Select* select[TypeSize];
    class Sound* sound = nullptr;

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Title();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Title();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>現在のシーンのポインタ</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// シーンの描画
    /// </summary>
    void Draw()override;

private:
    int graph;
    bool fadeLock;
};
