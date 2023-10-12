#pragma once

#include"../../Object/ObjectBase/ObjBase.h"

/// <summary>
/// UIBase�N���X
/// </summary>
class UIBase:public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="tag">:�^�O��</param>
    UIBase(ObjTag tag);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~UIBase();

    /// <summary>
    /// �N���b�N�\���
    /// </summary>
    /// <param name="colwidth">:�����蔻�蕝</param>
    /// <param name="colheight">:�����蔻�荂��</param>
    void CanClick(const int colwidth,const int colheight);

    /// <summary>
    /// �N���b�N����
    /// </summary>
    void MouseClick();

    /// <summary>
    /// �{�^�����͏�Ԏ擾
    /// </summary>
    /// <returns>����:true|������:false</returns>
    bool GetButtonInput() const { return isInput; }

    /// <summary>
    /// �L�[���͏�Ԏ擾
    /// </summary>
    /// <param name="keyName">:�L�[��</param>
    /// <returns>�L�[���͏��</returns>
    static int KeyStatus(int keyName);

protected:
    int mouseX;             //�}�E�X���WX
    int mouseY;             //�}�E�X���WY
    bool hasMauseClick;     //�}�E�X�N���b�N���
    bool canClick;          //�N���b�N�\���
    bool isInput;           //���͏��

    static int Key[256];    //�L�[
};