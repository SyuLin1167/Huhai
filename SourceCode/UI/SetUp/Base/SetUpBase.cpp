#include"SetUpBase.h"

// �R���X�g���N�^ //

SetUpBase::SetUpBase(std::string name)
    :UIBase(ObjTag::UI)
    , buttonName(name)
    , buttonWidth(0)
    , buttonHeight(0)
    , whiteColor(GetColor(255, 255, 255))
{
    AddFontResource("../Assets/Font/KillingFont.otf");
}

// �f�X�g���N�^ //

SetUpBase::~SetUpBase()
{
}

// ���͏��� //

void SetUpBase::ProcessInput()
{
    CanClick(buttonWidth, buttonHeight);
    MouseClick();
}

// ������̍��W�w��`�揈�� //

void SetUpBase::DrawStr(int x, int y)
{
    ChangeFont("KillingFont", DX_CHARSET_DEFAULT);
    DrawString(x, y, const_cast<const char*>(buttonName.c_str()), whiteColor);
    ChangeFont("�l�r�@�S�V�b�N", DX_CHARSET_DEFAULT);
}

// �{�^���̍��W�w��`�揈�� //

void SetUpBase::DrawButton(int x, int y)
{
    DrawBox(x, y, x + buttonWidth, y + buttonHeight, whiteColor, isInput);
}