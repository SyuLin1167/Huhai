
#include "SceneBase.h"

// �R���X�g���N�^ //

SceneBase::SceneBase()
    :BgHandle(-1)
    , BgX(0)
    , BgY(0)
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