#include "Door.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Sound/Sound.h"
#include"../../../UI/Action/Action.h"

// �R���X�g���N�^ //

Door::Door(VECTOR pos, VECTOR angle)
    :ObjBase(ObjectTag::Furniture, pos, angle)
    , doorAnim(nullptr)
    , animType(IDLE)
    , doorSound(nullptr)
    , rotateNow(true)
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

    //�A�j���[�V�����ݒ�
    doorAnim = new Animation(objHandle);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorOpen.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->StartAnim(animType);
    doorAnim->StopAnim();

    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;

    //�T�E���h�ݒ�
    doorSound = new Sound;
    doorSound->AddSound("../Assets/Sound/DoorOpenSE.wav", SoundTag::DoorOpen, true, true);
    doorSound->AddSound("../Assets/Sound/DoorCloseSE.wav", SoundTag::DoorClose, true, true);

    //�A�N�V�����{�^���ǉ�
    action = new Action(objPos);
    ObjManager::Entry(action);
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
        //�v���C���[���߂Â�����{�^���\��
        VECTOR actionPos = player->GetPos() - objPos;
        actionPos = VNorm(actionPos);
        action->SetPos(objPos + actionPos + VGet(0, 20, 0));

        if (!doorAnim->IsPlaying())
        {

            //E�L�[���͂Ńh�A�J��
            if (!action->IsVisible())
            {
                if (animType != OPEN)
                {
                    MoveAnim(OPEN);
                }
            }
            //Q�L�[���͂Ńh�A��
            if (CheckHitKey(KEY_INPUT_Q))
            {
                if (animType == OPEN)
                {
                    MoveAnim(CLOSE);
                }
            }
        }
    }

    //���f���̉�]
    MATRIX rotYMat = MGetRotY(90.0f * (float)(DX_PI / 180.0f));
    VECTOR negativeVec = VTransform(objDir, rotYMat);
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

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
            action->SetVisible(false);
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