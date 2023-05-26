#include "GhostBase.h"

GhostBase::GhostBase()
    :ObjectBase(ObjectTag::Ghost)
    , gstAnim(nullptr)
    , animType(IDLE)
{
    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../Assets/Chara/Ghost/GhostModel.mv1");        //���f���ǂݍ���
    MV1SetScale(objHandle, VGet(0.02f, 0.02f, 0.02f));                                  //���f���̃T�C�Y�ݒ�

    gstAnim = new Animation(objHandle);                                                 //�A�j���[�V�����̃C���X�^���X


    //---�A�j���[�V�����ǂݍ���---//
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostIdle.mv1");               //�ҋ@:0
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostWalk.mv1");                //����:1
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostSad.mv1");                //����:1
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostMove.mv1");                //����:1

    //---�A�j���[�V������ԃZ�b�g---//
    gstAnim->StartAnim(animType);
    objDir = VGet(-1.0f, 0.0f, 0.0f);                                                   //��������
    MV1SetPosition(objHandle, objPos);                                                  //�|�W�V�����ݒ�
}

GhostBase::~GhostBase()
{
    AssetManager::ReleaseMesh(objHandle);
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
    delete gstAnim;
}