#include "Ghost.h"
#include"../Player/Player.h"

/* @brief Ghostコンストラクタ */

Ghost::Ghost()
    :GhostBase()
{
    //---当たり判定球設定---//
    colSphere.localCenter = VGet(0, 10, 0);			//ローカル座標
    colSphere.Radius = 5.0f;						//球半径
    colSphere.worldCenter = objPos;					//ワールド座標

    objSpeed = 5.0f;
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

    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);



    MV1SetPosition(objHandle, objPos);                        //ポジション設定
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));       //左向きに回転させる
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);         //モデル回転

    
    colSphere.Move(objPos);					//当たり判定の移動
}

// @brief Ghost描画処理 //

void Ghost::Draw()
{
    MV1DrawModel(objHandle);

    ////---当たり判定デバッグ描画(後で消す)---//
    //DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
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

}
