#pragma once

#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../../Asset/Animation/Animation.h"
#include"../../../../Collision/Collision.h"
#include"../../../../Asset/Sound/Sound.h"

/*Ghost�̊��N���X*/
class GhostBase:public ObjectBase
{
public:
    /// <summary>
    /// GhostBase�R���X�g���N�^
    /// </summary>
    GhostBase();

    /// <summary>
    /// GhostBase�f�X�g���N�^
    /// </summary>
    ~GhostBase();

    /// <summary>
    /// �A�j���[�V�����X�e�[�^�X
    /// </summary>
    enum Anim
    {
        IDLE = 0,                           //�ҋ@
        WALK,                                //����
        SAD,
        MOVE,
    };

    /// <summary>
    /// �����蔻�苅�擾
    /// </summary>
    /// <returns>�����蔻�苅</returns>
    Sphere GetColSphere() { return colSphere; }

protected:
    //---�A�j���[�V�����֘A---//
    class Animation* gstAnim;                     //�A�j���[�V����
    int animType;                           //�A�j���[�V�������

    class Sound* gstSound;
};
