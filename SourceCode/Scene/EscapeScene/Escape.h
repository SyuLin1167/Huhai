#pragma once

#include"../SceneBase/SceneBase.h"

/*EscapeSceneクラス*/
class EscapeScene :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EscapeScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EscapeScene();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>次のフレームのシーン</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

private:
    class Blend* escBlend;    //ブレンドモード
    class Sound* escSound;        //サウンド
};

