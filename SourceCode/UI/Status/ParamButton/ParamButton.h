#pragma once
#include<string>

#include"../Base/StatusBase.h"

/// <summary>
/// ParamBottonクラス
/// </summary>
class ParamButton :public StatusBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name">:ボタン名</param>
    /// <param name="num">:ボタン番号</param>
    /// <param name="value">:パラメーター初期値</param>
    ParamButton(std::string name, int num,int value);

    /// <summary>
    /// 最小値最大値設定
    /// </summary>
    /// <param name="min">:パラメーター最大値</param>
    /// <param name="max">:パラメーター最小値</param>
    void ParamMinMax(int min,int max);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ParamButton();

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
    /// パラメーター取得
    /// </summary>
    /// <returns>:パラメーター</returns>
    int GetParam() { return param; }

private:
    const float PARAM_BUTTON_POS_X = SCREEN_WIDTH * 0.7f;     //ボタン座標X
    const float PARAM_BUTTON_POS_Y = SCREEN_HEIGHT / 9.0f;    //ボタン座標Y
    const int PARAM_BUTTON_SIZE_X = 70;     //ボタンサイズ
    const int PARAM_BUTTON_SIZE_Y = 45;     //ボタンサイズ

    const int PARAM_COLOR = GetColor(10, 255, 255);     //パラメーターの色
    int paramMin;                           //パラメーター最小値
    int paramMax;                           //パラメーター最大値
    
    int moveX;                              //移動量X
    int prevMousePosX;                      //過去のマウス座標X
    bool canMove;                           //移動可能状態


    int param;                              //パラメーター

    class BlendMode* paramButtonBlend;                //ブレンドモード
};

