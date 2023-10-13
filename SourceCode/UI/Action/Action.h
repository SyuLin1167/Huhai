#pragma once

#include"../../UI/UIBase/UIBase.h"

/// <summary>
/// Action�N���X
/// </summary>
class Action :public UIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">:�`����W</param>
    Action(VECTOR pos);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Action();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// ���A�N�V����
    /// </summary>
    /// <returns>������:true|������:false</returns>
    bool IsAction() const { return isAction; }

private:
    const VECTOR ACTION_ICON_POS_Y = { 0,20,0 };        //�A�C�R���̍���
    const float actionRange = 30.0f;                    //�͈�
    float toDistance;                                   //����

    bool canAction;                                     //�����\���
    bool isAction;                                      //�������

    const float EXTEND_RATE = 0.3f;                     //�L�k�l

    class BlendMode* actionBlend;                       //�u�����h���[�h
};
