#include "SceneBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase()
    :bgHandle(-1)
    , bgX(0)
    , bgY(0)
    , BLACK_SCREEN_COLOR(GetColor(0, 0, 0))
    ,blendMode(new BlendMode)
    ,sound(new Sound)
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
    //処理なし
}