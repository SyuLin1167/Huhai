#pragma once
#include<string>

#include"../../UIBase/UIBase.h"

/*SetUpBaseクラス*/
class SetUpBase :public UIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name">:ボタン名</param>
    SetUpBase(std::string name);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SetUpBase();

    /// <summary>
    /// 入力処理
    /// </summary>
    void ProcessInput();

    /// <summary>
    /// 文字列の座標指定描画処理
    /// </summary>
    /// <param name="x">:座標X</param>
    /// <param name="y">:座標Y</param>
    void DrawStr(int x, int y);

    /// <summary>
    /// ボタンの座標指定描画処理
    /// </summary>
    /// <param name="x">:座標X</param>
    /// <param name="y">:座標Y</param>
    void DrawButton(int x, int y);

protected:
    std::string buttonName;     //ボタン名
    int buttonWidth;            //ボタン幅
    int buttonHeight;           //ボタン高さ

    const int StrSpace = 300;   //ボタンとの間隔

    const int whiteColor;       //白色
};