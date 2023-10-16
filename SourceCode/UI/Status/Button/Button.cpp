#include "Button.h"

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
    objPos.x = BUTTON_POS_X;
    objPos.y = BUTTON_POS_Y * (num + 2);

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
/// <param name="deltaTime">:�f���^�^�C��</param>
void Button::Update(const float deltaTime)
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