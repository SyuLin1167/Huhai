#include "UIBase.h"

int UIBase::Key[256] = {};

// �R���X�g���N�^ //

UIBase::UIBase(ObjectTag tag)
    :ObjBase(tag)
    , mouseX(0)
    , mouseY(0)
    , hasMauseClick(false)
    , canClick(false)
    , isInput(false)
{

}

// �f�X�g���N�^ //

UIBase::~UIBase()
{

}

// �}�E�X���͉\��� //

void UIBase::CanClick(const int colwidth,const int colheight)
{
    //�}�E�X�J�[�\�����W�擾
    GetMousePoint(&mouseX, &mouseY);

    // �}�E�X���{�^����ɂ�������N���b�N�\�ɂ���
    if (objPos.x <= mouseX && objPos.x + colwidth >= mouseX &&
        objPos.y <= mouseY && objPos.y + colheight >= mouseY)
    {
        canClick = true;
    }
    else
    {
        //��{�̓N���b�N�s�\
        canClick = false;
    }
}

// �}�E�X���͏��� //

void UIBase::MouseClick()
{
    //�N���b�N�\��������
    if (canClick)
    {
        //�N���b�N������N���b�N���ɂ���
        if ((GetMouseInput() & MOUSE_INPUT_LEFT))
        {
            hasMauseClick = true;
        }
        else if(hasMauseClick)
        {
            //�N���b�N����͏�Ԃɂ���
            isInput = !isInput;
            hasMauseClick = false;
        }
    }
    else
    {
        //�N���b�N�s�\�Ȃ疢���͂ɂ���
        hasMauseClick = false;
    }
}

// �L�[���͏�Ԏ擾 //

int UIBase::KeyStatus(int keyName)
{
    GetHitKeyStateAllEx(Key);
    return Key[keyName];
}