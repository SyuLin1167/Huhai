#include "BlinkingLight.h"
#include"../../../../Shade/Bloom/Bloom.h"

// �R���X�g���N�^ //

BlinkingLight::BlinkingLight()
    :LightBase()
    , intervalTime(0.0f)
    , countTimer(0.0f)
    , isBlinking(false)
{
    Load();
}

// �R���X�g���N�^ //

BlinkingLight::BlinkingLight(VECTOR pos)
    :LightBase(pos)
{
    Load();
}

// �f�X�g���N�^ //

BlinkingLight::~BlinkingLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

// �ǂݍ��ݏ��� //

void BlinkingLight::Load()
{
    //���f���ݒ�
    MV1SetPosition(objHandle, objPos);
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

// �X�V���� //

void BlinkingLight::Update(float deltaTime)
{
    //�J�E���g���C���^�[�o���𒴂��邽�тɗ����𐶐�
    countTimer += deltaTime;
    if (countTimer >= intervalTime)
    {
        countTimer = 0;
        srand((unsigned int)time(NULL));
        intervalTime = static_cast <float>(rand() % 4 + 1);
    }

    //�C���^�[�o����1�b�ȉ���������_�ł�����
    if (intervalTime <= 1)
    {
        isBlinking = !isBlinking;
    }
    else
    {
        //��{�͓_�ł����Ȃ�
        isBlinking = false;
    }

    //�_�Ŏ��̓��C�g�̖��邳�ύX
    if (isBlinking)
    {
        SetLightRangeAttenHandle(lightHandle, lightRange, 0.0f, 0.0f, lightAtten2 + 0.001f);
        MV1SetMaterialEmiColor(objHandle, 0, GetColorF(0.8f, 0.8f, 0.8f, 0.8f));
    }
    else
    {
        SetLightRangeAttenHandle(lightHandle, lightRange, 0.0f, 0.0f, lightAtten2);
        MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
    }

    //�p�����[�^�[�ɂ�鋗������
    AttenByParam();
}

// �`�揈�� //

void BlinkingLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}