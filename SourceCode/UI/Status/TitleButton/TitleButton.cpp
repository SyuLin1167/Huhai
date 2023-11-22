#include "TitleButton.h"

#include"../../../GameSetting/GameSetting.h"
#include"../../../BlendMode/BlendMode.h"

TitleButton::TitleButton(int num)
    :StatusBase("BackToTitle")
{
    //ボタン設定
    buttonWidth = TITLE_BUTTON_WIDTH;
    buttonHeight = TITLE_BUTTON_HEIGHT;
    objPos.x = TITLE_BUTTON_POS_X;
    objPos.y = TITLE_BUTTON_POS_Y * (num + 2);

    titleButtonBlend = new BlendMode;
}

TitleButton::~TitleButton()
{
    //処理なし
}

void TitleButton::Update(const float deltaTime)
{
    ProcessInput();
}

void TitleButton::Draw()
{
    SetFontSize(FONT_SIZE);
    //ボタン描画
    if (hasMauseClick)
    {
        titleButtonBlend->Darken();
    }
    DrawStr(static_cast<int>(objPos.x), static_cast<int>(objPos.y));

    titleButtonBlend->NoBlend();
}

