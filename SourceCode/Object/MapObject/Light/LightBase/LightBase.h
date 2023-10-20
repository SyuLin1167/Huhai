#pragma once
#include<unordered_map>

#include"../../../ObjectBase/ObjBase.h"
#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"

/// <summary>
/// LightBase�N���X
/// </summary>
class LightBase :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    LightBase();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="scene">:�V�[����</param>
    /// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
    LightBase(std::string scene, std::string num);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~LightBase();

    /// <summary>
    /// �p�����[�^�ɂ�鋗������
    /// </summary>
    void AttenByParam();

protected:
    const float DECIMAL_CONV = 10000.0f;    //�\�i���ϊ��p

    int lightHandle;                        //���C�g�n���h��
    const float LIGHT_POS_Y = 35.5f;        //���C�g�̍���
    const float LIGHTMODEL_POS_Y = 33.0f;   //���f���̍���

    const float LIGHT_RANGE = 70.0f;        //���������L������
    const float MIN_ATTEN_PARAM=0.01f;      //�����ŏ��l
    float lightAtten2;                      //���������W��

    const COLOR_F LIGHT_MAT_COLOR;            //���C�g�̃}�e���A���J���[

};
