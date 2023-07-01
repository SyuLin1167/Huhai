#include "Door.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Sound/Sound.h"

// �R���X�g���N�^ //

Door::Door()
    :ObjBase(ObjectTag::Furniture)
    , doorAnim(nullptr)
    , doorSound(nullptr)
{
    Load();
}

// �R���X�g���N�^ //

Door::Door(VECTOR doorPos, VECTOR doorAngle)
    :ObjBase(ObjectTag::Furniture, doorPos, doorAngle)
    , doorAnim(nullptr)
    , doorSound(nullptr)
{
    Load();
}

// �f�X�g���N�^ //

Door::~Door()
{
    //�C���X�^���X�폜
    delete doorAnim;
    delete doorSound;
}

// �ǂݍ��ݏ��� //

void Door::Load()
{
    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Door/Door.mv1");
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));

    //�A�j���[�V�����ݒ�
    doorAnim = new Animation(objHandle);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorOpen.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    animType = IDLE;
    doorAnim->StartAnim(animType);
    doorAnim->StopAnim();

    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;

    //�T�E���h�ݒ�
    doorSound = new Sound;
    doorSound->AddSound("../Assets/Sound/DoorOpenSE.wav", SoundTag::DoorOpen, true);
    doorSound->AddSound("../Assets/Sound/DoorCloseSE.wav", SoundTag::DoorClose, true);
}

// �X�V���� //

void Door::Update(float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    doorAnim->AddAnimTime(deltaTime);

    //�h�A�̊J����
    player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        //�v���C���[����苗���߂Â��Ă�����
        if (CollisionPair(colSphere, player->GetColSphere()))
        {
            if (!doorAnim->IsPlaying())
            {
                //E�L�[���͂Ńh�A�J��
                if (CheckHitKey(KEY_INPUT_E))
                {
                    if (animType != OPEN)
                    {
                        MoveAnim(OPEN);
                    }
                }
                //Q�L�[���͂Ńh�A��
                if (CheckHitKey(KEY_INPUT_Q))
                {
                    if (animType != CLOSE)
                    {
                        MoveAnim(CLOSE);
                    }
                }
            }

        }
    }

    //�����蔻��X�V
    colModel = objHandle;
    ColUpdate();

    //�T�E���h�X�V
    doorSound->Doppler(SoundTag::DoorOpen, objPos);
    doorSound->Doppler(SoundTag::DoorClose, objPos);
}

// �A�j���[�V�������� //

void Door::MoveAnim(int animtype)
{
    //�w�肵���A�j���[�V�������Đ�����
    if (animType != animtype)
    {
        animType = animtype;
        doorAnim->StartAnim(animType);
        if (animtype == OPEN)
        {
            doorSound->StartSound(SoundTag::DoorOpen, DX_PLAYTYPE_BACK);
        }
        else if (animtype == CLOSE)
        {
            doorSound->StartSound(SoundTag::DoorClose, DX_PLAYTYPE_BACK);
        }
    }
}

// �`�揈�� //

void Door::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}