#include "UIBase.h"

int UIBase::Key[256] = {};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">:�^�O��</param>
UIBase::UIBase(ObjTag tag)
    :ObjBase(tag)
    , mouseX(0)
    , mouseY(0)
    , hasMauseClick(false)
    , canClick(false)
    , isInput(false)
{
    //�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UIBase::~UIBase()
{
    //�����Ȃ�
}

/// <summary>
/// �N���b�N�\���
/// </summary>
/// <param name="colwidth">:�����蔻�蕝</param>
/// <param name="colheight">:�����蔻�荂��</param>
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

/// <summary>
/// �N���b�N����
/// </summary>
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

/// <summary>
/// �L�[���͏�Ԏ擾
/// </summary>
/// <param name="keyName">:�L�[��</param>
/// <returns>�L�[���͏��</returns>
int UIBase::KeyStatus(int keyName)
{
    GetHitKeyStateAllEx(Key);
    return Key[keyName];
}