#include"StatusBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="name">:�{�^����</param>
StatusBase::StatusBase(std::string name)
    :UIBase(ObjTag::UI)
    , buttonName(name)
    , buttonWidth(0)
    , buttonHeight(0)
    , whiteColor(GetColor(255, 255, 255))
{
    AddFontResource("../Assets/Font/KillingFont.otf");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StatusBase::~StatusBase()
{
}

/// <summary>
/// ���͏���
/// </summary>
void StatusBase::ProcessInput()
{
    CanClick(buttonWidth, buttonHeight);
    MouseClick();
}

/// <summary>
/// ������̍��W�w��`�揈��
/// </summary>
/// <param name="x">:���WX</param>
/// <param name="y">:���WY</param>
void StatusBase::DrawStr(int x, int y)
{
    ChangeFont("KillingFont", DX_CHARSET_DEFAULT);
    DrawString(x, y, const_cast<const char*>(buttonName.c_str()), whiteColor);
    ChangeFont("�l�r�@�S�V�b�N", DX_CHARSET_DEFAULT);
}

/// <summary>
/// �{�^���̍��W�w��`�揈��
/// </summary>
/// <param name="x">:���WX</param>
/// <param name="y">:���WY</param>
void StatusBase::DrawButton(int x, int y)
{
    DrawBox(x, y, x + buttonWidth, y + buttonHeight, whiteColor, isInput);
}