#pragma once

#include <Dxlib.h>
#include<memory>
#include"../../GameSetting/GameSetting.h"
#include"../../BlendMode/BlendMode.h"
#include"../../Asset/Sound/Sound.h"

/// <summary>
/// SceneBaseクラス
/// </summary>
class SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneBase();

    /// <summary>
    /// Scene更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    /// <returns>現在のシーン</retdeltaTimeurns>
    virtual SceneBase* UpdateScene(const float deltaTime) = 0;

    /// <summary>
    /// シーンの描画
    /// </summary>
    virtual void DrawScene() = 0;

protected:
    int bgHandle;       //背景画像ハンドル
    int bgX;            //背景座標X
    int bgY;            //背景座標Y

    const int BLACK_SCREEN_COLOR; //スクリーンの色(ブラック)

    std::unique_ptr<BlendMode> blendMode;       //ブレンドモード
    std::unique_ptr<Sound> sound;               //サウンド
};
