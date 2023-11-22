#include "SceneBase.h"

SceneBase::SceneBase()
    :sceneName("")
    , bgHandle(-1)
    , bgX(0)
    , bgY(0)
    , BLACK_SCREEN_COLOR(GetColor(0, 0, 0))
    ,blendMode(new BlendMode)
    ,sound(new Sound)
{
    //ˆ—‚È‚µ
}

SceneBase::~SceneBase()
{
    //ˆ—‚È‚µ
}