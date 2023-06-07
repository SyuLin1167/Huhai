#include "GhostWalkGim.h"
#include"../../../MapObject/Light/NomalLight/NomalLight.h"
#include"../../Man/Man.h"

// @brief GhostWalkGimコンストラクタ //

GhostWalkGim::GhostWalkGim()
    :GhostBase()
    ,light(nullptr)
    ,move(false)
{
    objPos = VGet(120.0f, 0.0f, 65.0f);

    //---当たり判定球設定---//
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, -40);			//ローカル座標
    colSphere.Radius = 15.0f;						//球半径
    colSphere.worldCenter = objPos;					//ワールド座標

    objSpeed = 17.0f;
}

// @brief GhostWalkGimデストラクタ //

GhostWalkGim::~GhostWalkGim()
{
}

// @brief GhostWalkGim更新処理 //

void GhostWalkGim::Update(float deltaTime)
{
    gstAnim->AddAnimTime(deltaTime);
    if (move)
    {
        //---当たり判定線分設定---//
        ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
        colLine = Line(VGet(7.0f, 5.0f, 0.0f), player->GetPos() - objPos+VGet(0,5,0));             //線分設定

        objPos.x -= objSpeed * deltaTime;
    }

    MV1SetPosition(objHandle, objPos);                        //ポジション設定
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));       //左向きに回転させる
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);         //モデル回転

    ColUpdate();
}

// @brief GhostWalkGim描画処理 //

void GhostWalkGim::Draw()
{
    MV1DrawModel(objHandle);
}

// @brief GhostWalkGim衝突時処理 //

void GhostWalkGim::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();
    if (tag == ObjectTag::Player)
    {
        if (CollisionPair(colSphere, other->GetColSphere()))
        {
            if (animType != WALK)
            {
                animType = WALK;
                gstAnim->StartAnim(animType);
                gstSound->StartSound(SoundTag::GhostWalk, DX_PLAYTYPE_BACK);
                move = true;
                light = ObjManager::GetFirstObj(ObjectTag::Light);
                if (light)
                {
                    light->SetPos(VGet(-32, 32, 75));
                }
            }
        }
    }
    if (tag == ObjectTag::Map ||
        tag == ObjectTag::Furniture)                                      //マップとぶつかったら
    {
        int mapColModel = other->GetColModel();                        //モデル当たり判定取得
        //---マップと足元線分の当たり判定---//
        MV1_COLL_RESULT_POLY colInfoLine;                           //線分当たり判定情報
        if (CollisionPair(colLine, mapColModel, colInfoLine))
        {
            isVisible = false;
            if (!gstSound->IsPlaying(SoundTag::GhostWalk))
            {
                isAlive = false;
            }
            ColUpdate();
        }
    }
}
