#include "ObjectBase.h"

// @brief コンストラクター //

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

// @brief コンストラクター(位置・方向セット) //

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

// @brief Collision更新処理 //

void ObjectBase::ColUpdate()
{
    //---全当たり判定種の移動処理---//
    colLine.Move(objPos);
    colSphere.Move(objPos);
    colCapsule.Move(objPos);

    if (colModel != -1)                                         //モデルが空でなければ
    {
        MV1SetPosition(colModel, objPos);                       //位置設定
        MV1SetupCollInfo(colModel);                             //当たり判定情報構築
    }

}

// @brief Collision描画処理 //

void ObjectBase::ColDraw()
{
    //---全当たり判定種の描画処理---//
    DrawLine3D(colLine.worldStart, colLine.worldEnd, 
        GetColor(255, 255, 0));
    DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 10,
        GetColor(0, 255, 255),
        GetColor(0, 0, 0), FALSE);
    DrawCapsule3D(colCapsule.worldStart, colCapsule.worldEnd, colCapsule.Radius, 8,
        GetColor(255, 0, 255),
        GetColor(0, 0, 0), FALSE);

    if (colModel != -1)                                         //モデルが空でなければ
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);      //半透明にして
        MV1DrawModel(colModel);                             //モデル描画
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);    //以降は不透明
    }
}
