#include "ObjectBase.h"

// @brief �R���X�g���N�^�[ //

ObjectBase::ObjectBase(ObjectTag tag)
    :objTag(tag)
    , objHandle(-1)
    , objPos{ 0,0,0 }
    , objDir{ 0,0,0 }
    , objScale{ 0.1f,0.1f,0.1f }
    , objSpeed(20.0f)
    , isVisible(true)
    , isAlive(true)
    , moveModel(false)
    , colType()
    , colLine()
    , colSphere()
    , colCapsule()
    , colModel(-1)
{
}

// @brief �R���X�g���N�^�[(�ʒu�E�����Z�b�g) //

ObjectBase::ObjectBase(ObjectTag tag, VECTOR pos, VECTOR angle)
    :objTag(tag)
    , objHandle(-1)
    , objPos(pos)
    , objDir(angle)
    , objScale{ 0.1f,0.1f,0.1f }
    , objSpeed(20.0f)
    , isVisible(true)
    , isAlive(true)
    , moveModel(false)
    , colType()
    , colLine()
    , colSphere()
    , colCapsule()
    , colModel(-1)
{
}

// @brief �f�X�g���N�^�[ //

ObjectBase::~ObjectBase()
{
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
}

// @brief �`�揈�� //

void ObjectBase::Draw()
{
}

// @brief Collision�X�V���� //

void ObjectBase::ColUpdate()
{
    //---�S�����蔻���̈ړ�����---//
    colLine.Move(objPos);
    colSphere.Move(objPos);
    colCapsule.Move(objPos);

    if (colModel != -1)                                         //���f������łȂ����
    {
        MV1SetPosition(colModel, objPos);                       //�ʒu�ݒ�
        MV1SetupCollInfo(colModel);                             //�����蔻����\�z
    }

}

// @brief Collision�`�揈�� //

void ObjectBase::ColDraw()
{
    //---�S�����蔻���̕`�揈��---//
    DrawLine3D(colLine.worldStart, colLine.worldEnd, 
        GetColor(255, 255, 0));
    DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 10,
        GetColor(0, 255, 255),
        GetColor(0, 0, 0), FALSE);
    DrawCapsule3D(colCapsule.worldStart, colCapsule.worldEnd, colCapsule.Radius, 8,
        GetColor(255, 0, 255),
        GetColor(0, 0, 0), FALSE);

    if (colModel != -1)                                         //���f������łȂ����
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);      //�������ɂ���
        MV1DrawModel(colModel);                             //���f���`��
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);    //�ȍ~�͕s����
    }
}
