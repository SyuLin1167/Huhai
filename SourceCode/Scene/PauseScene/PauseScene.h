#pragma once
#include"../SceneBase/SceneBase.h"

/// <summary>
/// PauseSceneクラス
/// </summary>
class PauseScene:public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PauseScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PauseScene();

    /// <summary>
    /// ポーズメニュー初期化処理
    /// </summary>
    void InitPauesMenu();

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

private:
    const int PIXEL_WIDTH = 8;                                          //ピクセル幅
    const int GAUSS_PARAM = 1400;                                       //ぼかし値
};

