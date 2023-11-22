#include "Ghost.h"
#include"../Player/Player.h"
#include"../../MapObject/Light/FlashLight/FlashLight.h"

Ghost::Ghost()
    :GhostBase()
    , moveCount(7.0f)
    , isFirstMove(true)
    ,aimPos(VGet(0.0f, 0.0f, 0.0f))
    , lightHandle(-1)
    , holdPos(VGet(0.0f, 0.0f, 0.0f))
{
    aimDir = VGet(0.0f, 0.0f, 1.0f);
    objPos = VGet(0.0f, 0.0f, -45.0f);

    //アニメーション設定
    if (animType != SAD)
    {
        animType = SAD;
        ghostAnim->StartAnim(animType);
    }

    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5.0f, 0);
    colSphere.Radius = 3.0f;
    colSphere.worldCenter = objPos;
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -5.0f, 0.0f));

    //移動速度
    objSpeed = 13.0f;

    //サウンド設定
    ghostSound->StartSound(SoundTag::Escape, DX_PLAYTYPE_LOOP);
}

Ghost::~Ghost()
{
    //ライト削除
    DeleteLightHandle(lightHandle);

    //モデル削除
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
}

void Ghost::Update(float deltaTime)
{
    //アニメーション時間再生
    ghostAnim->AddAnimTime(deltaTime);

    //モデル回転
    MATRIX rotMatY = MGetRotY(PI_DEGREE * (float)(DX_PI / PI_DEGREE));
    VECTOR negativeVec = VTransform(objDir, rotMatY);
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
    rotateNow = true;
    Rotate();

    //初動時は指定座標へ移動
    if (moveCount >= 0.0f)
    {
        moveCount -= deltaTime;
    }
    //カウントがゼロになったら動作開始
    else if (isFirstMove)
    {
        //アニメーション&サウンド再生
        if (animType != MOVE)
        {
            animType = MOVE;
            ghostAnim->StartAnim(animType);

            //ライト設置
            ObjManager::GetFirstObj(ObjTag::Light)->SetVisible(false);
            lightHandle = CreatePointLightHandle(objPos, LIGHT_RANGE, 0.0f, 0.0f, LIGHT_ATTEN2);
            SetLightDifColorHandle(lightHandle, LIGHT_COLOR);

            ghostSound->StartSound(SoundTag::GhostScream, DX_PLAYTYPE_BACK);
        }
        //目標座標に近づいたら初動終了
        if (abs(VSize(aimPos - objPos)) < 2.0f)
        {
            isFirstMove = false;
        }
        isMove = true;
    }
    else
    {
        //基本目標座標はプレイヤー座標
        aimPos = ObjManager::GetFirstObj(ObjTag::Player)->GetPos();
    }

    //動作中は目標座標に向かって移動
    if (isMove)
    {
        VECTOR moveVec = aimPos - objPos;
        moveVec = VNorm(moveVec);
        objPos += moveVec * objSpeed * deltaTime;
        aimDir = moveVec;
        objPos.y = GHOST_MOVE_POS_Y;
    }
    MV1SetPosition(objHandle, objPos);                        //ポジション設定

    //ライト更新
    if (lightHandle)
    {
        SetLightPositionHandle(lightHandle, objPos + LIGHT_POS);
    }

    //当たり判定更新
    ColUpdate();

    //サウンド更新
    ghostSound->Doppler(SoundTag::GhostScream, objPos);
    ghostSound->Doppler(SoundTag::Escape, objPos);
}

void Ghost::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}

void Ghost::OnCollisionEnter(const ObjBase* other)
{
    ObjTag tag = other->GetTag();

    //建物にぶつかったら押し戻す
    if (tag == ObjTag::Map)
    {
        int colModel = other->GetColModel();
        //球体の当たり判定
        MV1_COLL_RESULT_POLY_DIM colInfo;
        if (CollisionPair(colSphere, colModel, colInfo))
        {
            VECTOR pushBack = CalcSpherePushBackFromMesh(colSphere, colInfo);
            objPos += pushBack;
            MV1CollResultPolyDimTerminate(colInfo);
            ColUpdate();
        }

        //線分の当たり判定
        MV1_COLL_RESULT_POLY colInfoLine;
        if (CollisionPair(colLine, colModel, colInfoLine))
        {
            objPos = colInfoLine.HitPosition;
            ColUpdate();
        }
    }

    //プレイヤーに当たったらゲームオーバーにする
    if (tag == ObjTag::Player)
    {
        if (abs(VSize(other->GetPos() - objPos)) < HIT_DISTANCE && !isFirstMove)
        {
            if (animType != SAD)
            {
                animType = SAD;
                ghostAnim->StartAnim(animType);
            }
            isMove = false;
            aimDir = VScale(VNorm(aimPos - objPos), 0.1f);
            ColUpdate();
        }
    }

}