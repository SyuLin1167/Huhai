#pragma once
#include<unordered_map>

#include"SelectType.h"
#include"../../UI/UIBase/UIBase.h"

/// <summary>
/// ボタンの選択
/// </summary>
class Select :public UIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="type">:ボタンタイプ</param>
    Select(SelectType type);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Select();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

private:
    const int BUTTON_WIDTH = 160;
    const int BUTTON_HEIGHT = 50;

    //描画座標を格納した配列
    std::unordered_map<SelectType, VECTOR> drawPos{
        {SelectType::PLAY,{125,680,0}},
        {SelectType::LOAD,{125,760,0}},
        {SelectType::EXIT,{125,840,0}},
    };

    //画像ハンドルを格納した配列
    std::unordered_map<SelectType, const char*> drawHandle{
        {SelectType::PLAY,"../Assets/BackGround/Play.png"},
        {SelectType::LOAD,"../Assets/BackGround/Load.png"},
        {SelectType::EXIT,"../Assets/BackGround/Exit.png"},
    };

    class BlendMode* selectBlend;    //ブレンドモード
};


