#include "Ghost.h"
#include"../Player/Player.h"
#include"../../MapObject/Light/FlashLight/FlashLight.h"

/* コンストラクタ */

Ghost::Ghost()
    :GhostBase()
    , moveCount(7.0f)
    , isFirstMove(true)
    , isMove(false)
    , rotateNow(false)
    ,aimPos(VGet(0.0f, 0.0f, 0.0f))
    , aimDir(VGet(0.0f, 0.0f, 1.0f))
    , lightHandle(-1)
    , holdPos(VGet(0.0f, 0.0f, 0.0f))
{
    objPos = VGet(0.0f, 0.0f, -45.0f);

    //アニメーション設定
    if (animType != SAD)
    {
        animType = SAD;
        gstAnim->StartAnim(animType);
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
    gstSound->StartSound(SoundTag::Escape, DX_PLAYTYPE_LOOP);
}

// デストラクタ //

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

// 更新処理 //

void Ghost::Update(float deltaTime)
{
    //アニメーション時間再生
    gstAnim->AddAnimTime(deltaTime);

    //モデル回転
    MATRIX rotMatY = MGetRotY(180 * (float)(DX_PI / 180.0f));
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
            gstAnim->StartAnim(animType);

            //ライト設置
            ObjManager::GetFirstObj(ObjectTag::Light)->SetAlive(false);
            lightHandle = CreatePointLightHandle(objPos, 50.0f, 0.0f, 0.0f, 0.005f);
            SetLightDifColorHandle(lightHandle, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));

            gstSound->StartSound(SoundTag::GhostScream, DX_PLAYTYPE_BACK);
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
        aimPos = ObjManager::GetFirstObj(ObjectTag::Player)->GetPos();
    }

    //動作中は目標座標に向かって移動
    if (isMove)
    {
        VECTOR moveVec = aimPos - objPos;
        moveVec = VNorm(moveVec);
        objPos += moveVec * objSpeed * deltaTime;
        aimDir = moveVec;
        objPos.y = 1.2f;
    }
    MV1SetPosition(objHandle, objPos);                        //ポジション設定

    //ライト更新
    if (lightHandle)
    {
        SetLightPositionHandle(lightHandle, objPos + VGet(0.0f, 10.0f, 0.0f));
    }

    //当たり判定更新
    ColUpdate();

    //サウンド更新
    gstSound->Doppler(SoundTag::GhostScream, objPos);
    gstSound->Doppler(SoundTag::Escape, objPos);
}

// 描画処理 //

void Ghost::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}

// 当たり判定処理 //

void Ghost::OnCollisionEnter(const ObjBase* other)
{
    ObjectTag tag = other->GetTag();

    //建物にぶつかったら押し戻す
    if (tag == ObjectTag::Map)
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
    if (tag == ObjectTag::Player)
    {
        if (abs(VSize(other->GetPos() - objPos)) < 12.0f && !isFirstMove)
        {
            if (animType != SAD)
            {
                animType = SAD;
                gstAnim->StartAnim(animType);
            }
            isMove = false;
            aimDir = VScale(VNorm(aimPos - objPos), 0.1f);
            ColUpdate();
        }
    }

}

// 回転処理 //

void Ghost::Rotate()
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
            interPolateDir = RotForAimY(objDir, aimDir, 5.0f);

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