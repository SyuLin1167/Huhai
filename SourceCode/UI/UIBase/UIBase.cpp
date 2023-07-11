#include "UIBase.h"

int UIBase::Key[256] = {};

// コンストラクタ //

UIBase::UIBase(ObjectTag tag)
    :ObjBase(tag)
    , mouseX(0)
    , mouseY(0)
    , hasMauseClick(false)
    , canClick(false)
    , isInput(false)
{

}

// デストラクタ //

UIBase::~UIBase()
{

}

// マウス入力可能状態 //

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

// マウス入力処理 //

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

// キー入力状態取得 //

int UIBase::KeyStatus(int keyName)
{
    GetHitKeyStateAllEx(Key);
    return Key[keyName];
}