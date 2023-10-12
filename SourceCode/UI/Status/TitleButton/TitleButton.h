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
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// 入力リセット
    /// </summary>
    void ChangeToFalse() { isInput = false; }
private:
    const int TITLE_BUTTON_WIDTH = 270;         //タイトルボタン幅
    const int TITLE_BUTTON_HEIGHT = 45;         //タイトルボタン高さ

    class BlendMode* titleButtonBlend;                    //ブレンドモード
};

