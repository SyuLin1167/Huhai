#include "BlendMode.h"

// @brief BlendMode�R���X�g���N�^ //

BlendMode::BlendMode()
    :fadeValue(0)
    ,nowFade(false)
    ,nowDark(false)
{
}

// @brief BlendMode�f�X�g���N�^ //

BlendMode::~BlendMode()
{
}

// @brief �t�F�[�h���Z //

void BlendMode::AddFade()
{
    if (fadeValue <= 255)                                    //((�l��255�ȉ���������))
    {
        nowFade = true;                                      //�t�F�[�h��
        fadeValue += fadeSpeed;                       //�l�ɑ��x�����Z
    }
    else                                                            //((��̏��������Ă͂܂�Ȃ��Ȃ�))
    {
        nowFade = false;                                     //�t�F�[�h���łȂ�
    }

}

// @brief �t�F�[�h���Z //

void BlendMode::SubFade()
{
    if (fadeValue >= 0)                                      //((�l��0�ȏゾ������))
    {
        nowFade = true;                                      //�t�F�[�h��
        fadeValue -= fadeSpeed;                       //�l�ɑ��x�����Z
    }
    else                                                            //((��̏��������Ă͂܂�Ȃ��Ȃ�))
    {
        nowFade = false;                                     //�t�F�[�h���łȂ�
    }
}

// @brief �t�F�[�h //

void BlendMode::Fade()
{
        //�`�t�F�[�h�����`//
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);         //�A���t�@�u�����h���[�h�ݒ�
}

// @brief �Ó]���� //

void BlendMode::Darken()
{
    if (nowFade)
    {
        nowDark = false;
    }
    else
    {
        SetDrawBlendMode(DX_BLENDMODE_ADD, darkValue);           //�T�u�u�����h���[�h
        nowDark = true;
    }
}

// @brief �f�t�H���g //

void BlendMode::NoBlend()
{
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);                      //�m�[�u�����h���[�h
}