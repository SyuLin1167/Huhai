#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"

/*脱出シーンクラス*/
class EscapeScene:public SceneBase
{
public:
    /// <summary>
    /// EscapeSceneコンストラクタ
    /// </summary>
    EscapeScene();

    /// <summary>
    /// EscapeSceneデストラクタ
    /// </summary>
    ~EscapeScene();

    /// <summary>
    /// EscapeScene更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>現在のシーンのポインタ</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// EscapeScene描画処理
    /// </summary>
    void Draw()override;

private:
    class BlendMode* escBlend;
    class Sound* escSound;
};

