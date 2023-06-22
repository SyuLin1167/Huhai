#include "GhostBase.h"

#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"

GhostBase::GhostBase()
    :ObjBase(ObjectTag::Ghost)
    , gstAnim(nullptr)
    , animType(IDLE)
    , gstSound(nullptr)
{
    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Chara/Ghost/GhostModel.mv1");
    objDir = VGet(-1.0f, 0.0f, 0.0f);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.02f, 0.02f, 0.02f));

    //�A�j���[�V�����ݒ�
    gstAnim = new Animation(objHandle);
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostIdle.mv1");
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostWalk.mv1");
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostSad.mv1");
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostMove.mv1");
    gstAnim->StartAnim(animType);

    //�T�E���h�ݒ�
    gstSound = new Sound;
    gstSound->AddSound("../Assets/Sound/GhostWalkSE.mp3", SoundTag::GhostWalk, 150);
    gstSound->AddSound("../Assets/Sound/GhostScreamSE.mp3", SoundTag::GhostScream, 300, true);
}

GhostBase::~GhostBase()
{
    //���f���폜
    AssetManager::ReleaseMesh(objHandle);

    //�C���X�^���X�폜
    delete gstAnim;
    delete gstSound;
}