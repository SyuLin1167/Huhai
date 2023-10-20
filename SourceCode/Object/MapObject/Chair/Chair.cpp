#include "Chair.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/Sound/Sound.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Chair::Chair()
    :ObjBase(ObjTag::Furniture)
    , chairSound(new Sound)
{
    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Chair/Chair.mv1");
    objPos = { 66,0,4 };
    objDir = { 0,-90,0 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / PI_DEGREE * DX_PI_F, 0.0f));

    //�A�j���[�V�����ݒ�
    chairAnim.reset(new Animation(objHandle));
    chairAnim->AddAnimation("../Assets/Map/Chair/Chair.mv1");
    chairAnim->AddAnimation("../Assets/Map/Chair/ChairMove.mv1", 30.0f, false);
    animType = IDLE;
    chairAnim->StartAnim(animType);

    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;
    colModel = objHandle;

    //�T�E���h�ݒ�
    chairSound->AddSound("../Assets/Sound/MoveChairSE.mp3", SoundTag::MoveChair, true, true);
    chairSound->AddSound("../Assets/Sound/FallingChairSE.mp3", SoundTag::FallingChair, true, true);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Chair::~Chair()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�f���^�^�C��</param>
void Chair::Update(const float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    chairAnim->AddAnimTime(deltaTime);

    //���쏈��
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        //�v���C���[����苗���߂Â����瓮�삷��
        if (CollisionPair(colSphere, player->GetColSphere()))
        {
            if (animType != MOVE)
            {
                animType = MOVE;
                chairAnim->StartAnim(animType);
                colModel = -1;
                chairSound->StartSoundOnce(SoundTag::MoveChair, DX_PLAYTYPE_BACK);
            }
        }
    }

    //�����蔻��X�V
    ColUpdate();

    //�T�E���h�X�V
    chairSound->Doppler(SoundTag::MoveChair,objPos);
    chairSound->Doppler(SoundTag::FallingChair, objPos);
}

/// <summary>
/// �`�揈��
/// </summary>
void Chair::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}