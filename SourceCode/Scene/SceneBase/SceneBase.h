#pragma once

#include <Dxlib.h>
#include<memory>
#include"../../BlendMode/BlendMode.h"
#include"../../Asset/Sound/Sound.h"

/*SceneBaseクラス*/
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
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>現在のシーン</retdeltaTimeurns>
    virtual SceneBase* UpdateScene(const float deltaTime) = 0;

    /// <summary>
    /// シーンの描画
    /// </summary>
    virtual void DrawScene() = 0;

protected:
    int BgHandle;       //背景画像ハンドル
    int BgX;            //背景座標X
    int BgY;            //背景座標Y

    std::unique_ptr<BlendMode> blendMode;       //ブレンドモード
    std::unique_ptr<Sound> sound;               //サウンド
};
