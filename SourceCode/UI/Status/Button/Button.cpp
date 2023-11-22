#include "Button.h"

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

Button::~Button()
{
    //処理なし
}

void Button::Update(const float deltaTime)
{
    ProcessInput();
}

void Button::Draw()
{
    //ボタン名描画
    SetFontSize(FONT_SIZE);
    DrawStr(static_cast<int>(objPos.x - StrSpace), static_cast<int>(objPos.y));

    //ボタン描画
    DrawButton(static_cast<int>(objPos.x), static_cast<int>(objPos.y));
}