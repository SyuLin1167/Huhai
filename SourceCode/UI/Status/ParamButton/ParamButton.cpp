#include "ParamButton.h"

#include"../../../GameSetting/GameSetting.h"
#include"../../../BlendMode/BlendMode.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="name">:ボタン名</param>
/// <param name="num">:ボタン番号</param>
/// <param name="value">:パラメーター初期値</param>
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
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (4.0f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 2) / 9.0f;

    paramButtonBlend = new BlendMode;
}

/// <summary>
/// 最小値最大値設定
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
void ParamButton::ParamMinMax(int min, int max)
{
    paramMin = min;
    paramMax = max;
}

/// <summary>
/// デストラクタ
/// </summary>
ParamButton::~ParamButton()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
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

/// <summary>
/// 描画処理
/// </summary>
void ParamButton::Draw()
{
    //パラメーター名描画
    SetFontSize(45);
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
        SetFontSize(25);
        DrawString(mouseX-PARAM_BUTTON_SIZE_Y/2, mouseY, "<  >", whiteColor);
    }
}