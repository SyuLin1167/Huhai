#pragma once
#include"../../Object/ObjectBase/ObjectBase.h"


/*ActionButton�N���X*/
class Action :public ObjBase
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
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// ���A�N�V����
    /// </summary>
    /// <returns>������:true|������:false</returns>
    bool IsAction() const { return isAction; }

private:
    const float actionRange = 30.0f;    //�͈�
    float toDistance;                   //����

    bool canAction;                     //�����\���
    bool isAction;                      //�������

    class BlendMode* actionBlend;       //�u�����h���[�h
};
