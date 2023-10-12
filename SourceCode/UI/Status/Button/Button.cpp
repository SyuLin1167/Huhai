#include "Button.h"
#include"../../../GameSetting/GameSetting.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="name">:�{�^����</param>
/// <param name="num">:�{�^���ԍ�</param>
Button::Button(std::string name, int num)
    :StatusBase(name)
{
    //�{�^���ݒ�
    buttonWidth = BUTTON_SIZE;
    buttonHeight = BUTTON_SIZE;
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (2.5f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 2) / 9.0f;

    isInput = true;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Button::~Button()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
void Button::Update(float deltaTime)
{
    ProcessInput();
}

/// <summary>
/// �`�揈��
/// </summary>
void Button::Draw()
{
    //�{�^�����`��
    SetFontSize(45);
    DrawStr(static_cast<int>(objPos.x) - StrSpace, static_cast<int>(objPos.y));

    //�{�^���`��
    DrawButton(static_cast<int>(objPos.x), static_cast<int>(objPos.y));
}