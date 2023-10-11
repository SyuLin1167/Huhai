#include "BlendMode.h"
#include<DxLib.h>
#include<math.h>
#include"../Object/ObjectBase/ObjBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="speed">:�t�F�[�h���x(�f�t�H���g�E80.0)</param>
BlendMode::BlendMode(float FadeSpeed)
    :fadeValue(0.0f)
    , fadeSpeed(FadeSpeed)
    , nowFade(false)
    , nowDark(false)
{
    // �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BlendMode::~BlendMode()
{
}

/// <summary>
/// �t�F�[�h�A�E�g
/// </summary>
void BlendMode::AddFade(float deltaTime)
{
    if (fadeValue <= 255)
    {
        //�l��255�ȉ���������t�F�[�h�A�E�g����
        nowFade = true;
        fadeValue += fadeSpeed * deltaTime;
        if (fadeValue <= 0)
        {
            fadeValue = 0;
        }
    }
    else
    {
        //��̏����ɓ��Ă͂܂�Ȃ��Ȃ�t�F�[�h���Ȃ�
        nowFade = false;
    }
}

/// <summary>
/// �t�F�[�h�C��
/// </summary>
void BlendMode::SubFade(float deltaTime)
{
    if (fadeValue >= 0)
    {
        //�l��0�ȏゾ������t�F�[�h�C������
        nowFade = true;
        fadeValue -= fadeSpeed * deltaTime;
        if (fadeValue >= 255)
        {
            fadeValue = 255;
        }
    }
    else 
    {
        //��̏����ɓ��Ă͂܂�Ȃ��Ȃ�t�F�[�h���Ȃ�
        nowFade = false;
    }
}

/// <summary>
/// �t�F�[�h
/// </summary>
void BlendMode::Fade()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeValue));
}

/// <summary>
/// �Ó]����
/// </summary>
void BlendMode::Darken()
{
    if (nowFade)
    {
        //�t�F�[�h����������Ó]���Ȃ�
        nowDark = false;
    }
    else
    {
        //�t�F�[�h���łȂ��Ȃ�Ó]����
        SetDrawBlendMode(DX_BLENDMODE_ADD, darkValue);
        nowDark = true;
    }
}

/// <summary>
/// �f�t�H���g
/// </summary>
void BlendMode::NoBlend()
{
    //�m�[�u�����h���[�h
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}