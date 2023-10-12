#include "ObjBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">:オブジェクトタグ</param>
ObjBase::ObjBase(ObjTag tag)
    :objTag(tag)
    , rotateNow(false)
    , aimDir{ 0,0,0 }
    , objHandle(-1)
    , objPos(VGet(0,0,0))
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
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ObjBase::~ObjBase()
{
    //処理なし
}

/// <summary>
/// 回転処理
/// </summary>
void ObjBase::Rotate()
{
    if (rotateNow)
    {
        // 回転が目標角度に十分近ければ回転モード終了
        if (IsSameAngle(aimDir, objDir))
        {
            objDir = aimDir;
            rotateNow = false;
        }
        else
        {
            // 回転させる
            VECTOR interPolateDir;
            interPolateDir = RotForAimY(objDir, aimDir, ROTATE_VELOCITY);

            // 回転が目標角度を超えていないか
            VECTOR cross1, cross2;
            cross1 = VCross(objDir, aimDir);
            cross2 = VCross(interPolateDir, aimDir);

            //目標角度を超えたら終了
            if (cross1.y * cross2.y < 0.0f)
            {
                interPolateDir = aimDir;
                rotateNow = false;
            }

            // 目標ベクトルに10度だけ近づけた角度
            objDir = interPolateDir;
        }
    }
}

/// <summary>
/// 当たり判定更新処理
/// </summary>
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