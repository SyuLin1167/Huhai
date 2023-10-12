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
    , ChairAnim(nullptr)
    , chairSound(nullptr)
{
    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Chair/Chair.mv1");
    objPos = { 66,0,4 };
    objDir = { 0,-90,0 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / ONE_HALF_PI * DX_PI_F, 0.0f));

    //�A�j���[�V�����ݒ�
    ChairAnim = new Animation(objHandle);
    ChairAnim->AddAnimation("../Assets/Map/Chair/Chair.mv1");
    ChairAnim->AddAnimation("../Assets/Map/Chair/ChairMove.mv1", 30.0f, false);
    animType = IDLE;
    ChairAnim->StartAnim(animType);

    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;
    colModel = objHandle;

    //�T�E���h�ݒ�
    chairSound = new Sound;
    chairSound->AddSound("../Assets/Sound/MoveChairSE.mp3", SoundTag::MoveChair, true, true);
    chairSound->AddSound("../Assets/Sound/FallingChairSE.mp3", SoundTag::FallingChair, true, true);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Chair::~Chair()
{
    //�C���X�^���X�폜
    delete ChairAnim;
    delete chairSound;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
void Chair::Update(float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    ChairAnim->AddAnimTime(deltaTime);

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
                ChairAnim->StartAnim(animType);
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