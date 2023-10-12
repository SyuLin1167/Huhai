#include"StatusBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="name">:ボタン名</param>
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
/// デストラクタ
/// </summary>
StatusBase::~StatusBase()
{
}

/// <summary>
/// 入力処理
/// </summary>
void StatusBase::ProcessInput()
{
    CanClick(buttonWidth, buttonHeight);
    MouseClick();
}

/// <summary>
/// 文字列の座標指定描画処理
/// </summary>
/// <param name="x">:座標X</param>
/// <param name="y">:座標Y</param>
void StatusBase::DrawStr(int x, int y)
{
    ChangeFont("KillingFont", DX_CHARSET_DEFAULT);
    DrawString(x, y, const_cast<const char*>(buttonName.c_str()), whiteColor);
    ChangeFont("ＭＳ　ゴシック", DX_CHARSET_DEFAULT);
}

/// <summary>
/// ボタンの座標指定描画処理
/// </summary>
/// <param name="x">:座標X</param>
/// <param name="y">:座標Y</param>
void StatusBase::DrawButton(int x, int y)
{
    DrawBox(x, y, x + buttonWidth, y + buttonHeight, whiteColor, isInput);
}