#pragma once
#include <Dxlib.h>

//カラービット数
constexpr int ColorBit = 16;

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
    virtual SceneBase* Update(float) = 0;

    /// <summary>
    /// シーンの描画
    /// </summary>
    virtual void Draw() = 0;

protected:
    int BgHandle;       //背景画像ハンドル
    int BgX;            //背景座標X
    int BgY;            //背景座標Y
};

class Save
{

};
