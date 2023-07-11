#pragma once

#include"../SceneBase/SceneBase.h"

/*RoomSceneクラス*/
class RoomScene :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    RoomScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~RoomScene();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>次フレームのシーン</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

private:
    class Blend* roomBlend;     //ブレンドモード
    class Sound* roomSound;     //サウンド
};
