#include "Button.h"
#include"../../../GameSetting/GameSetting.h"

// コンストラクタ //

Button::Button(std::string name, int num)
    :SetUpBase(name)
{
    //ボタン設定
    buttonWidth = BUTTON_SIZE;
    buttonHeight = BUTTON_SIZE;
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (2.5f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 3) / 9.0f;

    isInput = true;
}

// デストラクタ //

Button::~Button()
{
}

// 更新処理 //

void Button::Update(float deltaTime)
{
    ProcessInput();
}

// 描画処理 //

void Button::Draw()
{
    //ボタン名描画
    SetFontSize(45);
    DrawStr(static_cast<int>(objPos.x) - StrSpace, static_cast<int>(objPos.y));

    //ボタン描画
    DrawButton(static_cast<int>(objPos.x), static_cast<int>(objPos.y));
}