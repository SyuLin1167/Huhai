#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// RoomSceneクラス
/// </summary>
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
    /// <param name="deltaTime">:デルタタイム</param>
    /// <returns>次フレームのシーン</returns>
    SceneBase* UpdateScene(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void DrawScene() override;
};
