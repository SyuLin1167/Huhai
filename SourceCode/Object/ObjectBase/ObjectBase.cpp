#include "ObjectBase.h"

// @brief �R���X�g���N�^�[ //

ObjectBase::ObjectBase(ObjectTag tag)
    :objTag(tag)
    , objHandle(-1)
    , objPos{0,0,0}
    , objDir{0,0,0}
    ,objScale{0.1f,0.1f,0.1f}
    , objSpeed(0.0f)
    ,isVisible(true)
    , isAlive(true)
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