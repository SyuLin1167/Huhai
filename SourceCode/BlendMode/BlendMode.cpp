#include "BlendMode.h"
#include<DxLib.h>
#include<math.h>
#include"../Object/ObjectBase/ObjectBase.h"

// �R���X�g���N�^ //

Blend::Blend(float FadeSpeed)
    :fadeValue(0.0f)
    , fadeSpeed(FadeSpeed)
    , nowFade(false)
    , nowDark(false)
{
    // �����Ȃ�
}

// �f�X�g���N�^ //

Blend::~Blend()
{
}

// �t�F�[�h�A�E�g //

void Blend::AddFade(float deltaTime)
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

// �t�F�[�h�C�� //

void Blend::SubFade(float deltaTime)
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

// �t�F�[�h //

void Blend::Fade()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeValue));
}

// �Ó]���� //

void Blend::Darken()
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

// �f�t�H���g //

void Blend::NoBlend()
{
    //�m�[�u�����h���[�h
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}