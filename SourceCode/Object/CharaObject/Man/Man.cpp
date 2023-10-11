#include "Man.h"

#include "../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../UI/Action/Action.h"
#include"../../../UI/Reamarks/Remarks.h"
#include"../../../Asset/Sound/Sound.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Man::Man()
    :ObjBase(ObjTag::Man)
    , isSpeak(false)
    , manAnim(new Animation(objHandle))
    , manSound(new Sound)
{
    Load();
}

// �f�X�g���N�^ //

Man::~Man()
{
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
    manAnim->AddAnimation("../Assets/Chara/Man/ManCrying.mv1");
    manAnim->AddAnimation("../Assets/Chara/Man/ManDying.mv1", 30.0f, false);
    animType = CRYING;
    manAnim->StartAnim(animType);

    //�T�E���h�ݒ�
    manSound->AddSound("../Assets/Sound/ManHurtSE.mp3", SoundTag::ManHurt, true);
    manSound->AddSound("../Assets/Sound/BodyFallSE.mp3", SoundTag::BodyFall, true);

    //�A�N�V�����{�^������
    ObjManager::AddObj(new Action(objPos + VGet(0, 0, 5)));
}

// �X�V���� //

void Man::Update(float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    manAnim->AddAnimTime(deltaTime);

    //���f���̉�]
    MATRIX rotYMat = MGetRotY(ONE_HALF_PI * (float)(DX_PI / ONE_HALF_PI));
    VECTOR negativeVec = VTransform(objDir, rotYMat);

    //�A�N�V�����{�^���������ꂽ��Z���t���Đ�
    if (!ObjManager::GetObj(ObjTag::UI, 3)->IsVisible())
    {
        //�v���C���[�̕�������
        rotateNow = true;
        aimDir = VSub(ObjManager::GetFirstObj(ObjTag::Player)->GetPos(), objPos);
        aimDir = VNorm(aimDir);
        Rotate();

        //�Z���t���I�������j�������S������
        ObjBase* remarks = ObjManager::GetFirstObj(ObjTag::Remarks);
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
            ObjManager::AddObj(new Remarks(TextType::ManSpeak));
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