#pragma once
#include<string>

#include"../Base/StatusBase.h"

/// <summary>
/// TitleButtonクラス
/// </summary>
class TitleButton :public StatusBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="num">:ボタン番号</param>
    TitleButton(int num);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TitleButton();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

    /// <summary>
    /// 入力リセット
    /// </summary>
    void ChangeToFalse() { isInput = false; }
private:
    const float TITLE_BUTTON_POS_X = SCREEN_WIDTH * 0.41f;      //ボタン座標X
    const float TITLE_BUTTON_POS_Y = SCREEN_HEIGHT / 9.0f;      //ボタン座標Y
    const int TITLE_BUTTON_WIDTH = 270;                         //タイトルボタン幅
    const int TITLE_BUTTON_HEIGHT = 45;                         //タイトルボタン高さ

    class BlendMode* titleButtonBlend;                          //ブレンドモード
};

