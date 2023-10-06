#pragma once
#include<string>

#include"../Base/SetUpBase.h"

/*ParamButton�N���X*/
class ParamButton :public SetUpBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name">:�{�^����</param>
    /// <param name="num">:�{�^���ԍ�</param>
    /// <param name="value">:�p�����[�^�[�����l</param>
    ParamButton(std::string name, int num,int value);

    /// <summary>
    /// �ŏ��l�ő�l�ݒ�
    /// </summary>
    /// <param name="min"></param>
    /// <param name="max"></param>
    void ParamMinMax(int min,int max);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ParamButton();

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
    /// �p�����[�^�[�擾
    /// </summary>
    /// <returns>:�p�����[�^�[</returns>
    int GetParam() { return param; }

private:
    const int PARAM_BUTTON_SIZE_X = 70;     //�{�^���T�C�Y
    const int PARAM_BUTTON_SIZE_Y = 45;     //�{�^���T�C�Y

    const int PARAM_COLOR = GetColor(10, 255, 255);     //�p�����[�^�[�̐F
    int paramMin;                           //�p�����[�^�[�ŏ��l
    int paramMax;                           //�p�����[�^�[�ő�l
    
    int moveX;                              //�ړ���X
    int prevMousePosX;                      //�ߋ��̃}�E�X���WX
    bool canMove;                           //�ړ��\���


    int param;                              //�p�����[�^�[

    class BlendMode* paramButtonBlend;                //�u�����h���[�h
};

