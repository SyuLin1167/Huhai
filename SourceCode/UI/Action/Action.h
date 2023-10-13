#pragma once

#include"../../UI/UIBase/UIBase.h"

/// <summary>
/// Actionクラス
/// </summary>
class Action :public UIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">:描画座標</param>
    Action(VECTOR pos);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Action();

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
    /// リアクション
    /// </summary>
    /// <returns>反応中:true|無反応:false</returns>
    bool IsAction() const { return isAction; }

private:
    const VECTOR ACTION_ICON_POS_Y = { 0,20,0 };        //アイコンの高さ
    const float actionRange = 30.0f;                    //範囲
    float toDistance;                                   //距離

    bool canAction;                                     //反応可能状態
    bool isAction;                                      //反応状態

    const float EXTEND_RATE = 0.3f;                     //伸縮値

    class BlendMode* actionBlend;                       //ブレンドモード
};
