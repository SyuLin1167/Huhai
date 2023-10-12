#include "TitleButton.h"

#include"../../../GameSetting/GameSetting.h"
#include"../../../BlendMode/BlendMode.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="num">:ボタン番号</param>
TitleButton::TitleButton(int num)
    :StatusBase("BackToTitle")
{
    //ボタン設定
    buttonWidth = TITLE_BUTTON_WIDTH;
    buttonHeight = TITLE_BUTTON_HEIGHT;
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (2.5f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 2) / 9.0f;

    titleButtonBlend = new BlendMode;
}

/// <summary>
/// デストラクタ
/// </summary>
TitleButton::~TitleButton()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void TitleButton::Update(float deltaTime)
{
    ProcessInput();
}

/// <summary>
/// 描画処理
/// </summary>
void TitleButton::Draw()
{
    SetFontSize(45);
    //ボタン描画
    if (hasMauseClick)
    {
        titleButtonBlend->Darken();
    }
    DrawStr(static_cast<int>(objPos.x), static_cast<int>(objPos.y));

    titleButtonBlend->NoBlend();
}

