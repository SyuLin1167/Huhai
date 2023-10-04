
#include "SceneBase.h"

// コンストラクタ //

SceneBase::SceneBase()
    :BgHandle(-1)
    , BgX(0)
    , BgY(0)
    ,blendMode(new BlendMode)
    ,sound(new Sound)
{
    //処理なし
}

// デストラクタ //

SceneBase::~SceneBase()
{
    //処理なし
}