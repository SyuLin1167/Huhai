#include "UIBase.h"

int UIBase::Key[256] = {};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">:タグ名</param>
UIBase::UIBase(ObjTag tag)
    :ObjBase(tag)
    , mouseX(0)
    , mouseY(0)
    , hasMauseClick(false)
    , canClick(false)
    , isInput(false)
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
UIBase::~UIBase()
{
    //処理なし
}

/// <summary>
/// クリック可能状態
/// </summary>
/// <param name="colwidth">:当たり判定幅</param>
/// <param name="colheight">:当たり判定高さ</param>
void UIBase::CanClick(const int colwidth,const int colheight)
{
    //マウスカーソル座標取得
    GetMousePoint(&mouseX, &mouseY);

    // マウスがボタン上にあったらクリック可能にする
    if (objPos.x <= mouseX && objPos.x + colwidth >= mouseX &&
        objPos.y <= mouseY && objPos.y + colheight >= mouseY)
    {
        canClick = true;
    }
    else
    {
        //基本はクリック不可能
        canClick = false;
    }
}

/// <summary>
/// クリック処理
/// </summary>
void UIBase::MouseClick()
{
    //クリック可能だったら
    if (canClick)
    {
        //クリックしたらクリック中にする
        if ((GetMouseInput() & MOUSE_INPUT_LEFT))
        {
            hasMauseClick = true;
        }
        else if(hasMauseClick)
        {
            //クリック後入力状態にする
            isInput = !isInput;
            hasMauseClick = false;
        }
    }
    else
    {
        //クリック不可能なら未入力にする
        hasMauseClick = false;
    }
}

/// <summary>
/// キー入力状態取得
/// </summary>
/// <param name="keyName">:キー名</param>
/// <returns>キー入力状態</returns>
int UIBase::KeyStatus(int keyName)
{
    GetHitKeyStateAllEx(Key);
    return Key[keyName];
}