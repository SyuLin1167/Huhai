#include "Button.h"
#include"../../../GameSetting/GameSetting.h"

// �R���X�g���N�^ //

Button::Button(std::string name, int num)
    :SetUpBase(name)
{
    //�{�^���ݒ�
    buttonWidth = BUTTON_SIZE;
    buttonHeight = BUTTON_SIZE;
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (2.5f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 2) / 9.0f;

    isInput = true;
}

// �f�X�g���N�^ //

Button::~Button()
{
}

// �X�V���� //

void Button::Update(float deltaTime)
{
    ProcessInput();
}

// �`�揈�� //

void Button::Draw()
{
    //�{�^�����`��
    SetFontSize(45);
    DrawStr(static_cast<int>(objPos.x) - StrSpace, static_cast<int>(objPos.y));

    //�{�^���`��
    DrawButton(static_cast<int>(objPos.x), static_cast<int>(objPos.y));
}