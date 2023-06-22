#include "ObjectBase.h"

// �R���X�g���N�^ //

ObjBase::ObjBase(ObjectTag tag)
    :objTag(tag)
    , objHandle(-1)
    , objPos(VGet(0.0f,0.0f,0.0f))
    , objDir(VGet(1.0f, 0.0f, 0.0f))
    , objScale(VGet(0.1f, 0.1f, 0.1f))
    , objSpeed(20.0f)
    , isVisible(true)
    , isAlive(true)
    , colType()
    , colLine()
    , colSphere()
    , colCapsule()
    , colModel(-1)
{
}

// �R���X�g���N�^(�ʒu�E�����Z�b�g) //

ObjBase::ObjBase(ObjectTag tag, VECTOR pos, VECTOR angle)
    :objTag(tag)
    , objHandle(-1)
    , objPos(pos)
    , objDir(angle)
    , objScale(VGet(0.1f, 0.1f, 0.1f))
    , objSpeed(20.0f)
    , isVisible(true)
    , isAlive(true)
    , colType()
    , colLine()
    , colSphere()
    , colCapsule()
    , colModel(-1)
{
}

// �f�X�g���N�^ //

ObjBase::~ObjBase()
{
}

// Collision�X�V���� //

void ObjBase::ColUpdate()
{
    //�S�����蔻��X�V
    colLine.Move(objPos);
    colSphere.Move(objPos);
    colCapsule.Move(objPos);

    if (colModel != -1)
    {
        MV1SetPosition(colModel, objPos);
        MV1SetupCollInfo(colModel);
    }
}