#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// EndingSceneクラス
/// </summary>
class EndingScene :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EndingScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EndingScene();

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
