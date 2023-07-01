#include "Wipe.h"
#include<DxLib.h>
#include<math.h>
#include"../Object/ObjectBase/ObjectBase.h"

// �R���X�g���N�^ //

Wipe::Wipe(float FadeSpeed)
    :fadeValue(0.0f)
    , fadeSpeed(FadeSpeed)
    , nowFade(false)
    , nowDark(false)
    , screenGraph(MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE))
    , gaussGraph(MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE))
    , gaussValue(0.0f)
{
}

// �f�X�g���N�^ //

Wipe::~Wipe()
{
}

// �t�F�[�h�A�E�g //

void Wipe::AddFade(float deltaTime)
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

void Wipe::SubFade(float deltaTime)
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

void Wipe::Fade()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeValue));
}

// �Ó]���� //

void Wipe::Darken()
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

void Wipe::NoBlend()
{
    //�m�[�u�����h���[�h
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// �A�Q //

void Wipe::Sleep(float deltaTime)
{
    //�u��������
    if (gaussValue < DX_PI_F*3)
    {
        gaussValue += 0.05f ;
    }
}

// �A�Q�`�揈�� //

void Wipe::SleepDraw()
{
    //�`��������ʂɂ��đS�̂�Ԃɂ���
    SetDrawScreen(screenGraph);

    //�ڂ���
    GraphFilterBlt(screenGraph, gaussGraph, DX_GRAPH_FILTER_GAUSS, 16, 200 * sin(gaussValue));

    //�`���𗠉�ʂɕύX
    SetDrawScreen(DX_SCREEN_BACK);

    //�摜�`��
    DrawGraph(0, 0, gaussGraph, TRUE);
}