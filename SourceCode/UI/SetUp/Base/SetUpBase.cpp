#include"SetUpBase.h"

// コンストラクタ //

SetUpBase::SetUpBase(std::string name)
    :UIBase(ObjTag::UI)
    , buttonName(name)
    , buttonWidth(0)
    , buttonHeight(0)
    , whiteColor(GetColor(255, 255, 255))
{
    AddFontResource("../Assets/Font/KillingFont.otf");
}

// デストラクタ //

SetUpBase::~SetUpBase()
{
}

// 入力処理 //

void SetUpBase::ProcessInput()
{
    CanClick(buttonWidth, buttonHeight);
    MouseClick();
}

// 文字列の座標指定描画処理 //

void SetUpBase::DrawStr(int x, int y)
{
    ChangeFont("KillingFont", DX_CHARSET_DEFAULT);
    DrawString(x, y, const_cast<const char*>(buttonName.c_str()), whiteColor);
    ChangeFont("ＭＳ　ゴシック", DX_CHARSET_DEFAULT);
}

// ボタンの座標指定描画処理 //

void SetUpBase::DrawButton(int x, int y)
{
    DrawBox(x, y, x + buttonWidth, y + buttonHeight, whiteColor, isInput);
}