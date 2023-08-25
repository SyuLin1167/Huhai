#include "TitleButton.h"

#include"../../../GameSetting/GameSetting.h"
#include"../../../BlendMode/BlendMode.h"

// コンストラクタ //

TitleButton::TitleButton(int num)
    :SetUpBase("BackToTitle")
{
    //ボタン設定
    buttonWidth = TITLE_BUTTON_WIDTH;
    buttonHeight = TITLE_BUTTON_HEIGHT;
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (2.5f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 2) / 9.0f;

    titleButtonBlend = new Blend;
}

// デストラクタ //

TitleButton::~TitleButton()
{
}

// 更新処理 //

void TitleButton::Update(float deltaTime)
{
    ProcessInput();
}

// 描画処理 //

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

