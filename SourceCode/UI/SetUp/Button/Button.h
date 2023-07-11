#pragma once
#include<string>

#include"../../SetUp/Base/SetUpBase.h"

/*Buttonクラス*/
class Button:public SetUpBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name">:ボタン名</param>
    /// <param name="num">:ボタン番号</param>
    Button(std::string name,int num);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Button();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

private:
    const int BUTTON_SIZE = 45;                         //ボタンサイズ
};

