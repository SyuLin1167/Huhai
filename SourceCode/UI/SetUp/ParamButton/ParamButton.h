#pragma once
#include<string>

#include"../Base/SetUpBase.h"

/*ParamButtonクラス*/
class ParamButton :public SetUpBase
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
    /// デストラクタ
    /// </summary>
    ~ParamButton();

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
    /// パラメーター取得
    /// </summary>
    /// <returns>:パラメーター</returns>
    int GetParam() { return param; }

private:
    const int PARAM_BUTTON_SIZE_X = 70;     //ボタンサイズ
    const int PARAM_BUTTON_SIZE_Y = 45;     //ボタンサイズ
    const int PARAM_MIN = 1;                //パラメーター最小値
    const int PARAM_MAX = 255;              //パラメーター最大値
    
    int moveX;                              //移動量X
    int prevMousePosX;                      //過去のマウス座標X
    bool canMove;                           //移動可能状態


    int param;                              //パラメーター

    class Blend* paramButtonBlend;                //ブレンドモード
};

