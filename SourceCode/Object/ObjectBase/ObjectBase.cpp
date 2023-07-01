#include "ObjectBase.h"

// コンストラクタ //

ObjBase::ObjBase(ObjectTag tag)
    :objTag(tag)
    , objHandle(-1)
    , objPos(zeroVec)
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

// コンストラクタ(位置・方向セット) //

ObjBase::ObjBase(ObjectTag tag, VECTOR pos, VECTOR dir)
    :objTag(tag)
    , objHandle(-1)
    , objPos(pos)
    , objDir(dir)
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

// デストラクタ //

ObjBase::~ObjBase()
{
}

// Collision更新処理 //

void ObjBase::ColUpdate()
{
    //全当たり判定更新
    colLine.Move(objPos);
    colSphere.Move(objPos);
    colCapsule.Move(objPos);

    if (colModel != -1)
    {
        MV1SetPosition(colModel, objPos);
        MV1SetupCollInfo(colModel);
    }
}