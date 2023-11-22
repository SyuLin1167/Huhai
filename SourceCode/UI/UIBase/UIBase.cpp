#include "UIBase.h"

int UIBase::Key[256] = {};

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

UIBase::~UIBase()
{
    //処理なし
}

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

int UIBase::KeyStatus(int keyName)
{
    GetHitKeyStateAllEx(Key);
    return Key[keyName];
}