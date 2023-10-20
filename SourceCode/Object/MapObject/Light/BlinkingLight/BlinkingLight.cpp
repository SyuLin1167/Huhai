#include "BlinkingLight.h"
#include"../../../../Shade/Bloom/Bloom.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">:�V�[����</param>
/// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
BlinkingLight::BlinkingLight(std::string scene, std::string num)
    :LightBase(scene,num)
    , intervalTime(0.0f)
    , countTimer(0.0f)
    , isBlinking(false)
{
    //�����Ȃ�
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
BlinkingLight::~BlinkingLight()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�f���^�^�C��</param>
void BlinkingLight::Update(const float deltaTime)
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
            SetLightRangeAttenHandle(lightHandle, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2 + BLINK_PARAM);
            MV1SetMaterialEmiColor(objHandle, 0, BLINK_COLOR);
        }
        else
        {
            SetLightRangeAttenHandle(lightHandle, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);
            MV1SetMaterialEmiColor(objHandle, 0, LIGHT_MAT_COLOR);
        }

        //�p�����[�^�[�ɂ�鋗������
        AttenByParam();
}

/// <summary>
/// �`�揈��
/// </summary>
void BlinkingLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}