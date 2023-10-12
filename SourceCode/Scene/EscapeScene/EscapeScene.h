#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// EscapeSceneクラス
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
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>次のフレームのシーン</returns>
    SceneBase* UpdateScene(const float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void DrawScene()override;
};

