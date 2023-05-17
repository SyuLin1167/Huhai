#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"
#include"../../BlendMode/BlendMode.h"


/* タイトルシーンのクラス */
class Title :public SceneBase
{
    class Door* door = nullptr;
    class Select* select = nullptr;
    class BlendMode* titleBlend;

public:
    /// <summary>
    /// TitleSceneコンストラクタ
    /// </summary>
    Title();

    /// <summary>
    /// TitleSceneデストラクタ
    /// </summary>
    ~Title();

    /// <summary>
    /// TitleScene更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>現在のシーンのポインタ</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// TitleSceneシーンの描画
    /// </summary>
    void Draw()override;

private: 
    int graph;
    bool fadeLock;
};
