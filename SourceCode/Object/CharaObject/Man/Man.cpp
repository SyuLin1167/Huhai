#include "Man.h"

#include "../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../UI/Action/Action.h"
#include"../../../UI/Reamarks/Remarks.h"
#include"../../../Asset/Sound/Sound.h"

// �R���X�g���N�^ //

Man::Man()
    :ObjBase(ObjectTag::Man)
    , manAnim(nullptr)
    , rotateNow(false)
    , aimDir{ 0,0,0 }
    , isSpeak(false)
    , manSound(nullptr)
{
    Load();
}

// �f�X�g���N�^ //

Man::~Man()
{
    //���f���폜
    AssetManager::ReleaseMesh(objHandle);

    //�C���X�^���X�폜
    delete manAnim;
    delete manSound;
}

// �ǂݍ��ݏ��� //

void Man::Load()
{
    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Chara/Man/ManModel.mv1");
    objPos = { -55.0f,0.0f,30.0f };
    objDir = { 0,0,-1 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.02f, 0.02f, 0.02f));

    //�A�j���[�V�����ݒ�
    manAnim = new Animation(objHandle);
    manAnim->AddAnimation("../Assets/Chara/Man/ManCrying.mv1");
    manAnim->AddAnimation("../Assets/Chara/Man/ManDying.mv1", 30.0f, false);
    animType = CRYING;
    manAnim->StartAnim(animType);

    //�T�E���h�ݒ�
    manSound = new Sound;
    manSound->AddSound("../Assets/Sound/ManHurtSE.mp3", SoundTag::ManHurt, true);
    manSound->AddSound("../Assets/Sound/BodyFallSE.mp3", SoundTag::BodyFall, true);

    //�A�N�V�����{�^������
    ObjManager::Entry(new Action(objPos + VGet(0, 0, 5)));
}

// �X�V���� //

void Man::Update(float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    manAnim->AddAnimTime(deltaTime);

    //���f���̉�]
    MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
    VECTOR negativeVec = VTransform(objDir, rotYMat);

    //�A�N�V�����{�^���������ꂽ��Z���t���Đ�
    if (!ObjManager::GetObj(ObjectTag::UI, 3)->IsVisible())
    {
        //�v���C���[�̕�������
        rotateNow = true;
        aimDir = VSub(ObjManager::GetFirstObj(ObjectTag::Player)->GetPos(), objPos);
        aimDir = VNorm(aimDir);
        Rotate();

        //�Z���t���I�������j�������S������
        ObjBase* remarks = ObjManager::GetFirstObj(ObjectTag::Remarks);
        if (!remarks && isSpeak)
        {
            if (animType != DEAD)
            {
                animType = DEAD;
                manAnim->StartAnim(animType);
                manSound->StartSound(SoundTag::ManHurt, DX_PLAYTYPE_BACK);
            }
            if (!manSound->IsPlaying(SoundTag::ManHurt))
            {
                manSound->StartSound(SoundTag::BodyFall, DX_PLAYTYPE_BACK);
            }
        }
        if (animType == DEAD && !manAnim->IsPlaying())
        {
            isAlive = false;
        }

        //�����I��������b���ɂ���
        if (!rotateNow && !isSpeak)
        {
            ObjManager::Entry(new Remarks(TextType::ManSpeak));
            isSpeak = true;
        }
    }

    // ���f���ɉ�]���Z�b�g����
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    //�T�E���h�X�V
    manSound->Doppler(SoundTag::ManHurt,objPos);
    manSound->Doppler(SoundTag::BodyFall, objPos);
}

// �`�揈�� //

void Man::Draw()
{
    MV1DrawModel(objHandle);
}

// ��]���� //

void Man::Rotate()
{
    if (rotateNow)
    {
        // ��]���ڕW�p�x�ɏ\���߂���Ή�]���[�h�I��
        if (IsSameAngle(aimDir, objDir))
        {
            objDir = aimDir;
            rotateNow = false;
        }
        else
        {
            // ��]������
            VECTOR interPolateDir;
            interPolateDir = RotForAimY(objDir, aimDir, 5.0f);

            // ��]���ڕW�p�x�𒴂��Ă��Ȃ���
            VECTOR cross1, cross2;
            cross1 = VCross(objDir, aimDir);
            cross2 = VCross(interPolateDir, aimDir);

            //�ڕW�p�x�𒴂�����I��
            if (cross1.y * cross2.y < 0.0f)
            {
                interPolateDir = aimDir;
                rotateNow = false;
            }
            // �ڕW�x�N�g����10�x�����߂Â����p�x
            objDir = interPolateDir;
        }
    }
}