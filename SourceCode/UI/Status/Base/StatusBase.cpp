#include"StatusBase.h"

StatusBase::StatusBase(std::string name)
    :UIBase(ObjTag::UI)
    , buttonName(name)
    , buttonWidth(0)
    , buttonHeight(0)
    , whiteColor(GetColor(255, 255, 255))
{
    AddFontResource("../Assets/Font/KillingFont.otf");
}

StatusBase::~StatusBase()
{
    //èàóùÇ»Çµ
}

void StatusBase::ProcessInput()
{
    CanClick(buttonWidth, buttonHeight);
    MouseClick();
}

void StatusBase::DrawStr(int x, int y)
{
    ChangeFont(killingFont, DX_CHARSET_DEFAULT);
    DrawString(x, y, const_cast<const char*>(buttonName.c_str()), whiteColor);
    ChangeFont(msGothic, DX_CHARSET_DEFAULT);
}

void StatusBase::DrawButton(int x, int y)
{
    DrawBox(x, y, x + buttonWidth, y + buttonHeight, whiteColor, isInput);
}