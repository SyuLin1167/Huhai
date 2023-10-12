#pragma once

#include"../../Object/ObjectBase/ObjBase.h"

/// <summary>
/// UIBaseクラス
/// </summary>
class UIBase:public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="tag">:タグ名</param>
    UIBase(ObjTag tag);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~UIBase();

    /// <summary>
    /// クリック可能状態
    /// </summary>
    /// <param name="colwidth">:当たり判定幅</param>
    /// <param name="colheight">:当たり判定高さ</param>
    void CanClick(const int colwidth,const int colheight);

    /// <summary>
    /// クリック処理
    /// </summary>
    void MouseClick();

    /// <summary>
    /// ボタン入力状態取得
    /// </summary>
    /// <returns>入力:true|未入力:false</returns>
    bool GetButtonInput() const { return isInput; }

    /// <summary>
    /// キー入力状態取得
    /// </summary>
    /// <param name="keyName">:キー名</param>
    /// <returns>キー入力状態</returns>
    static int KeyStatus(int keyName);

protected:
    int mouseX;             //マウス座標X
    int mouseY;             //マウス座標Y
    bool hasMauseClick;     //マウスクリック状態
    bool canClick;          //クリック可能状態
    bool isInput;           //入力状態

    static int Key[256];    //キー
};