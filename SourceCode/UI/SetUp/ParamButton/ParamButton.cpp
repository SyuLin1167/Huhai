#include "ParamButton.h"

#include"../../../GameSetting/GameSetting.h"
#include"../../../BlendMode/BlendMode.h"

// �R���X�g���N�^ //

ParamButton::ParamButton(std::string name, int num, int value)
    :SetUpBase(name)
    , paramMin(0)
    , paramMax(255)
    , moveX(0)
    , prevMousePosX(0)
    , param(value)
    , canMove(false)
{
    //�{�^���ݒ�
    buttonWidth = PARAM_BUTTON_SIZE_X;
    buttonHeight = PARAM_BUTTON_SIZE_Y;
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (4.0f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 2) / 9.0f;

    paramButtonBlend = new BlendMode;
}

// �ŏ��l�ő�l�ݒ� //

void ParamButton::ParamMinMax(int min, int max)
{
    paramMin = min;
    paramMax = max;
}

// �f�X�g���N�^ //

ParamButton::~ParamButton()
{
}

// �X�V���� //

void ParamButton::Update(float deltaTime)
{
    //�}�E�X���͏���
    ProcessInput();
    if (hasMauseClick)
    {
        canMove = true;
    }

    //�}�E�X�ړ��ʂŃp�����[�^�[��ϊ�����
    if (canMove && (GetMouseInput() & MOUSE_INPUT_LEFT))
    {
        moveX = prevMousePosX - mouseX;
        //�l�̐���
        if (param < paramMin)
        {
            param = paramMin;
            canMove = false;
        }
        else if (param > paramMax)
        {
            param = paramMax;
            canMove = false;
        }
        else
        {
            param -= moveX;
        }
    }
    else
    {
        canMove = false;
    }
    prevMousePosX = mouseX;


    isInput = false;
}

// �`�揈�� //

void ParamButton::Draw()
{
    //�p�����[�^�[���`��
    SetFontSize(45);
    DrawStr(static_cast<int>(objPos.x) - StrSpace, static_cast<int>(objPos.y));

    //�N���b�N���̉��o
    if (canClick)
    {
        paramButtonBlend->Darken();
    }

    //�p�����[�^�[�`��
    DrawFormatString(static_cast<int>(objPos.x), static_cast<int>(objPos.y), PARAM_COLOR, "%d", param);
    DrawButton(static_cast<int>(objPos.x), static_cast<int>(objPos.y));

    paramButtonBlend->NoBlend();

    //�K�C�h�`��
    if (canMove)
    {
        SetFontSize(25);
        DrawString(mouseX-PARAM_BUTTON_SIZE_Y/2, mouseY, "<  >", whiteColor);
    }
}