#pragma once
#include<unordered_map>

#include"LightPosTag.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"

        /*Light�̊��N���X*/
class LightBase :public ObjectBase
{
public:
    /// <summary>
    /// LightBase�R���X�g���N�^
    /// </summary>
    LightBase();

    /// <summary>
    /// LightBase�R���X�g���N�^
    /// </summary>
    /// <param name="lightPos">���C�g�̃��[���h���W</param>
    LightBase(VECTOR lightPos);

    /// <summary>
    /// LightBase�̃f�X�g���N�^
    /// </summary>
    ~LightBase();

    /// <summary>
    /// LightBase�ǂݍ��ݏ���
    /// </summary>
    void Load();

protected:
    int lightHandle;

    float lightRange;			//���������L������
    float lightAtten2;			//���������W��

    COLOR_F lightMatColor;		//���C�g�̃}�e���A���J���[

};
