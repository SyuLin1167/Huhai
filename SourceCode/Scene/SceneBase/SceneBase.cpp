#include "SceneBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
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

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{
    //�����Ȃ�
}