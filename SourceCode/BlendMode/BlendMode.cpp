#include "BlendMode.h"
#include<DxLib.h>
#include<math.h>
#include"../Object/ObjectBase/ObjBase.h"

BlendMode::BlendMode(float FadeSpeed)
    :fadeValue(0.0f)
    , fadeSpeed(FadeSpeed)
    , nowFade(false)
    , nowDark(false)
{
    // �����Ȃ�
}

BlendMode::~BlendMode()
{
    //�����Ȃ�
}

void BlendMode::AddFade(const float deltaTime)
{
    if (fadeValue <= MAX_ALPHA)
    {
        //�l��255�ȉ���������t�F�[�h�A�E�g����
        nowFade = true;
        fadeValue += fadeSpeed * deltaTime;
        if (fadeValue <= MIN_ALPHA)
        {
            fadeValue = static_cast<float>(MIN_ALPHA);
        }
    }
    else
    {
        //��̏����ɓ��Ă͂܂�Ȃ��Ȃ�t�F�[�h���Ȃ�
        nowFade = false;
    }
}

void BlendMode::SubFade(const float deltaTime)
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

void BlendMode::Fade()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeValue));
}

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
        SetDrawBlendMode(DX_BLENDMODE_ADD, DARK_VALUE);
        nowDark = true;
    }
}

void BlendMode::NoBlend()
{
    //�m�[�u�����h���[�h
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MIN_ALPHA);
}