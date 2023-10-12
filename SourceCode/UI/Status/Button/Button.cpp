#include "Button.h"
#include"../../../GameSetting/GameSetting.h"

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
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (2.5f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 2) / 9.0f;

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
/// <param name="deltaTime">:フレームレート</param>
void Button::Update(float deltaTime)
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