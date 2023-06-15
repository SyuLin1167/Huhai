#include "Door.h"
#include"../../../Asset/Sound/Sound.h"

        // �R���X�g���N�^ //

Door::Door()
    :ObjectBase(ObjectTag::Furniture)
    , doorAnim(nullptr)
    , doorModel(nullptr)
    , doorSound(nullptr)
{
    Load();
}

        // �R���X�g���N�^ //

Door::Door(VECTOR doorPos, VECTOR doorAngle)
    :ObjectBase(ObjectTag::Furniture, doorPos, doorAngle)
    , doorAnim(nullptr)
    , doorModel(nullptr)
    , doorSound(nullptr)
{
    Load();
}

        // �f�X�g���N�^ //

Door::~Door()
{
    delete doorAnim;
}

        // �ǂݍ��ݏ��� //

void Door::Load()
{
    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../Assets/Map/Door/Door.mv1");            //���f���ǂݍ���

    MV1SetPosition(objHandle, objPos);                                                      //���f���̍��W�ݒ�
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));                                                       //���f���̃T�C�Y�ݒ�
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //���f���̌����ݒ�

    //---�A�j���[�V�����ǂݍ���---//
    doorAnim = new Animation(objHandle);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);                        //�ҋ@:0
    doorAnim->AddAnimation("../Assets/Map/Door/DoorOpen.mv1", 30.0f, false);      //�J:1
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);     //��:2

    animType = IDLE;
    doorAnim->StartAnim(animType);
    doorAnim->StopAnim();

    colType = CollisionType::Sphere;                                                         //�����蔻��͋���

    colSphere.localCenter = VGet(0, 5, 0);                                                 //���[�J�����W
    colSphere.Radius = 15.0f;                                                                //�����a
    colSphere.worldCenter = objPos;                                                          //���[���h���W

    doorSound = new Sound;
    doorSound->AddSound("../Assets/Sound/DoorOpenSE.wav", SoundTag::DoorOpen, 150, true);
    doorSound->AddSound("../Assets/Sound/DoorCloseSE.wav", SoundTag::DoorClose, 150, true);
}

        // @brief Door�X�V���� //

void Door::Update(float deltaTime)
{
    doorAnim->AddAnimTime(deltaTime);

    //---�����蔻��ݒ�---//
    player = ObjManager::GetFirstObj(ObjectTag::Player);         //�v���C���[�I�u�W�F�N�g�擾
    if (player)                                                              //�I�u�W�F�N�g�̒��g����łȂ����
    {
        if (CollisionPair(colSphere, player->GetColSphere()))
        {
            if (!doorAnim->IsPlaying())
            {
                if (CheckHitKey(KEY_INPUT_E))                //E�L�[����
                {
                    if (animType != OPEN)															//���݂̃A�j���[�V�������w�肵���A�j���[�V��������Ȃ�������
                    {
                        MoveAnim(OPEN);
                    }
                }
                if (CheckHitKey(KEY_INPUT_Q))                //Q�L�[����
                {
                    if (animType != CLOSE)															//���݂̃A�j���[�V�������w�肵���A�j���[�V��������Ȃ�������
                    {
                        MoveAnim(CLOSE);
                    }
                }
            }

        }
    }
    colModel = objHandle;                                           //�����蔻��̃��f���̓I�u�W�F�N�g�̃��f��
    ColUpdate();

    doorSound->Update(objPos);
}

        // @brief Door�A�j���[�V��������

void Door::MoveAnim(int animtype)
{
    if (animType != animtype)															//���݂̃A�j���[�V�������w�肵���A�j���[�V��������Ȃ�������
    {
        animType = animtype;														//���݂̃A�j���[�V�������w�肵���A�j���[�V�����ɂ���
        doorAnim->StartAnim(animType);												//�A�j���[�V�����J�n
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

        // @brief Door�`�揈�� //

void Door::Draw()
{
    MV1DrawModel(objHandle);						//���f���`��
}