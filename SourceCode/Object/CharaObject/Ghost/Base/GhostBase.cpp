#include "GhostBase.h"

#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"

GhostBase::GhostBase()
    :ObjBase(ObjTag::Ghost)
    , isMove(false)
    , animType(Anim::IDLE)
    , ghostSound(new Sound)
{
    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Chara/Ghost/GhostModel.mv1");
    objDir = VGet(-1.0f, 0.0f, 0.0f);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.02f, 0.02f, 0.02f));

    //アニメーション設定
    ghostAnim.reset(new Animation(objHandle));
    ghostAnim->AddAnimation("../Assets/Chara/Ghost/GhostIdle.mv1");
    ghostAnim->AddAnimation("../Assets/Chara/Ghost/GhostWalk.mv1");
    ghostAnim->AddAnimation("../Assets/Chara/Ghost/GhostSad.mv1");
    ghostAnim->AddAnimation("../Assets/Chara/Ghost/GhostMove.mv1");
    ghostAnim->StartAnim(animType);

    //サウンド設定
    ghostSound->AddSound("../Assets/Sound/GhostWalkSE.mp3", SoundTag::GhostWalk);
    ghostSound->AddSound("../Assets/Sound/GhostScreamSE.mp3", SoundTag::GhostScream, true, true);
    ghostSound->AddSound("../Assets/Sound/EscapeBgm.mp3", SoundTag::Escape, true, false);
}

GhostBase::~GhostBase()
{
    //処理なし
}