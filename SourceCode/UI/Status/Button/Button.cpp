#include "Button.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="name">:ボタン名</param>
/// <param name="num">:ボタン番号</param>
Button::Button(std::string name, int num)
    :StatusBase(name)
{
    //ボタン設定
    buttonWidth = BUTTON_SIZE;
    buttonHeight = BUTTON_SIZE;
    objPos.x = BUTTON_POS_X;
    objPos.y = BUTTON_POS_Y * (num + 2);

    isInput = true;
}

/// <summary>
/// デストラクタ
/// </summary>
Button::~Button()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
void Button::Update(const float deltaTime)
{
    ProcessInput();
}

/// <summary>
/// 描画処理
/// </summary>
void Button::Draw()
{
    //ボタン名描画
    SetFontSize(45);
    DrawStr(static_cast<int>(objPos.x) - StrSpace, static_cast<int>(objPos.y));

    //ボタン描画
    DrawButton(static_cast<int>(objPos.x), static_cast<int>(objPos.y));
}