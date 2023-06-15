#include "Ghost.h"
#include"../Player/Player.h"
#include"../../MapObject/Light/FlashLight/FlashLight.h"

        /* @brief Ghostコンストラクタ */

Ghost::Ghost()
    :GhostBase()
    , moveCount(0.0f)
    , firstMove(true)
    , nowMove(false)
    , rotateNow(false)
    , aimDir(VGet(0.0f, 0.0f, 1.0f))
    , lightHandle(-1)
    , holdPos(VGet(0.0f, 0.0f, 0.0f))
{
    if (animType != SAD)
    {
        animType = SAD;
        gstAnim->StartAnim(animType);
    }
    objPos = VGet(0.0f, 0.0f, -45.0f);

    //---当たり判定球設定---//
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5.0f, 0);			//ローカル座標
    colSphere.Radius = 3.0f;						//球半径
    colSphere.worldCenter = objPos;					//ワールド座標

    //---当たり判定線分設定---//
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -5.0f, 0.0f));             //線分設定

    objSpeed = 13.0f;

}

        // @brief Ghostデストラクタ //

Ghost::~Ghost()
{
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
}

        // @brief Ghost更新処理 //

void Ghost::Update(float deltaTime)
{
    gstAnim->AddAnimTime(deltaTime);
    gstSound->Update(objPos);
    MATRIX rotMatY = MGetRotY(180 * (float)(DX_PI / 180.0f));       //左向きに回転させる
    objDir.y = 0;
    VECTOR negativeVec = VTransform(objDir, rotMatY);
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);         //モデル回転

    rotateNow = true;
    Rotate();


    if (firstMove)
    {
        moveCount += deltaTime;
        if (moveCount >= 7.0f)
        {
            nowMove = true;
            if (animType != MOVE)
            {
                animType = MOVE;
                gstAnim->StartAnim(animType);
                gstSound->StartSound(SoundTag::GhostScream, DX_PLAYTYPE_BACK);
                ObjManager::GetFirstObj(ObjectTag::Light)->SetAlive(false);
                lightHandle = CreatePointLightHandle(objPos, 50.0f, 0.0f, 0.0f, 0.005f);
                SetLightDifColorHandle(lightHandle, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
                aimPos = VGet(0.0f, 0.0f, 0.0f);
            }
            if (abs(VSize(aimPos - objPos)) < 2.0f)
            {
                firstMove = false;
            }
        }
    }
    else
    {
        aimPos = ObjManager::GetFirstObj(ObjectTag::Player)->GetPos();
    }

    if (nowMove)
    {
        VECTOR moveVec = aimPos - objPos;
        moveVec = VNorm(moveVec);
        objPos += moveVec * objSpeed * deltaTime;
        aimDir = moveVec;
    }

    if (lightHandle)
    {
        SetLightPositionHandle(lightHandle, objPos + VGet(0.0f, 10.0f, 0.0f));
    }

    MV1SetPosition(objHandle, objPos);                        //ポジション設定

    ColUpdate();            //当たり判定の移動
}

        // @brief Ghost描画処理 //

void Ghost::Draw()
{
    MV1DrawModel(objHandle);
}

        // @brief Ghost衝突時処理 //

void Ghost::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();

    if (tag == ObjectTag::Map)                                      //マップとぶつかったら
    {
        int colModel = other->GetColModel();                        //モデル当たり判定取得

        //---マップと境界球都の当たり判定---//
        MV1_COLL_RESULT_POLY_DIM colInfo;                          //モデル当たり判定情報
        if (CollisionPair(colSphere, colModel, colInfo))
        {
            VECTOR pushBack = CalcSpherePushBackFromMesh(colSphere, colInfo);   //押し戻し量算出
            objPos += pushBack;                                                         //押し戻す
            MV1CollResultPolyDimTerminate(colInfo);                        //当たり判定情報解放
            ColUpdate();
        }

        //---マップと足元線分の当たり判定---//
        MV1_COLL_RESULT_POLY colInfoLine;                           //線分当たり判定情報
        if (CollisionPair(colLine, colModel, colInfoLine))
        {
            objPos = colInfoLine.HitPosition;                       //足元を衝突時の座標に合わせる
            ColUpdate();
        }
    }

    if (tag == ObjectTag::Player)
    {
        if (abs(VSize(other->GetPos() - objPos)) < 12.0f && !firstMove)
        {
            if (animType != SAD)
            {
                animType = SAD;
                gstAnim->StartAnim(animType);
            }
            nowMove = false;
            aimDir = VScale(VNorm(aimPos - objPos), 0.1f);
            ColUpdate();
        }
    }

}

        // @brief Ghost回転処理 //

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