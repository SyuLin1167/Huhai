#pragma once
#include<unordered_map>

#include"LightPosTag.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"

/*Light���N���X*/
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
    /// <param name="pos">���[���h���W</param>
    LightBase(VECTOR pos);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~LightBase();

    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    void Load();

protected:
    int lightHandle;            //���C�g�n���h��

    float lightRange;			//���������L������
    float lightAtten2;			//���������W��

    COLOR_F lightMatColor;		//���C�g�̃}�e���A���J���[

};
