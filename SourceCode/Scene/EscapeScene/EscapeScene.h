#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// 脱出のシーン
/// </summary>
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
    /// <param name="deltaTime">:デルタタイム</param>
    /// <returns>次のフレームのシーン</returns>
    SceneBase* UpdateScene(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void DrawScene() override;
};

