#include "ParamButton.h"
#include"../../../BlendMode/BlendMode.h"

ParamButton::ParamButton(std::string name, int num, int value)
    :StatusBase(name)
    , paramMin(0)
    , paramMax(255)
    , moveX(0)
    , prevMousePosX(0)
    , param(value)
    , canMove(false)
{
    //ボタン設定
    buttonWidth = PARAM_BUTTON_SIZE_X;
    buttonHeight = PARAM_BUTTON_SIZE_Y;
    objPos.x = PARAM_BUTTON_POS_X;
    objPos.y = PARAM_BUTTON_POS_Y * (num + 2);

    paramButtonBlend = new BlendMode;
}

void ParamButton::ParamMinMax(int min, int max)
{
    paramMin = min;
    paramMax = max;
}

ParamButton::~ParamButton()
{
    //処理なし
}

void ParamButton::Update(const float deltaTime)
{
    //マウス入力処理
    ProcessInput();
    if (hasMauseClick)
    {
        canMove = true;
    }

    //マウス移動量でパラメーターを変換する
    if (canMove && (GetMouseInput() & MOUSE_INPUT_LEFT))
    {
        moveX = prevMousePosX - mouseX;
        //値の制限
        if (param < paramMin)
        {
            param = paramMin;
            canMove = false;
        }
        else if (param > paramMax)
        {
            param = paramMax;
            canMove = false;
        }
        else
        {
            param -= moveX;
        }
    }
    else
    {
        canMove = false;
    }
    prevMousePosX = mouseX;


    isInput = false;
}

void ParamButton::Draw()
{
    //パラメーター名描画
    SetFontSize(FONT_SIZE);
    DrawStr(static_cast<int>(objPos.x) - StrSpace, static_cast<int>(objPos.y));

    //クリック時の演出
    if (canClick)
    {
        paramButtonBlend->Darken();
    }

    //パラメーター描画
    DrawFormatString(static_cast<int>(objPos.x), static_cast<int>(objPos.y), PARAM_COLOR, "%d", param);
    DrawButton(static_cast<int>(objPos.x), static_cast<int>(objPos.y));

    paramButtonBlend->NoBlend();

    //ガイド描画
    if (canMove)
    {
        SetFontSize(GIDE_FONT_SIZE);
        DrawString(mouseX - PARAM_BUTTON_SIZE_Y / 2, mouseY, "<  >", whiteColor);
    }
}