#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// プレイのシーン
/// </summary>
class PlayScene :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PlayScene();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    /// <returns>次のフレームのシーン</returns>
    SceneBase* UpdateScene(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void DrawScene() override;
};