#include "ObjectBase.h"

// @brief コンストラクター //

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

// @brief デストラクター //
ObjectBase::~ObjectBase()
{
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
}

// @brief 描画処理 //

void ObjectBase::Draw()
{
}