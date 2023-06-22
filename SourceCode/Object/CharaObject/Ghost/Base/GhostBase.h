#pragma once

#include"../../../ObjectBase/ObjectBase.h"
#include"../../../../Asset/Animation/Animation.h"
#include"../../../../Asset/Sound/Sound.h"

/*GhostBase�N���X*/
class GhostBase :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GhostBase();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GhostBase();

    /// <summary>
    /// �A�j���[�V�����^�C�v
    /// </summary>
    enum Anim
    {
        IDLE = 0,                           //�ҋ@
        WALK,                               //����
        SAD,                                //����
        MOVE,                               //����
    };

protected:
    class Animation* gstAnim;       //�A�j���[�V����
    int animType;                   //�A�j���[�V�����^�C�v

    class Sound* gstSound;          //�T�E���h
};