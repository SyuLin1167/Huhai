#pragma once
#include<memory>

#include"../../../ObjectBase/ObjBase.h"
#include"../../../../Asset/Animation/Animation.h"
#include"../../../../Asset/Sound/Sound.h"

/// <summary>
/// �H��̊��N���X
/// </summary>
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
    bool isMove;                                    //�ړ����

    std::unique_ptr<class Animation> ghostAnim;     //�A�j���[�V����
    int animType;                                   //�A�j���[�V�����^�C�v

    std::unique_ptr<class Sound> ghostSound;        //�T�E���h
};