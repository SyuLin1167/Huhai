#include "SceneBase.h"

// �R���X�g���N�^ //

SceneBase::SceneBase()
    :bgHandle(-1)
    , bgX(0)
    , bgY(0)
    , BLACK_SCREEN_COLOR(GetColor(0, 0, 0))
    ,blendMode(new BlendMode)
    ,sound(new Sound)
{
    //�����Ȃ�
}

// �f�X�g���N�^ //

SceneBase::~SceneBase()
{
    //�����Ȃ�
}