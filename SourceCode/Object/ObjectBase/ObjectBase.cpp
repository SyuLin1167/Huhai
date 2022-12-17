#include "ObjectBase.h"

// @brief コンストラクター //

ObjectBase::ObjectBase(ObjectTag tag)
    :objTag(tag)
    , objHandle(-1)
    , objPos(VGet(0.0f, 0.0f, 0.0f))
    , objDir(VGet(0.0f, 0.0f, 0.0f))
    , objSpeed(0.0f)
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