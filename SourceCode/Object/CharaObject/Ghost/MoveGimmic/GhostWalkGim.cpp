#include "GhostWalkGim.h"

#include"../../../MapObject/Light/NomalLight/NomalLight.h"
#include"../../../MapObject/Door/Door.h"
#include"../../Man/Man.h"

// コンストラクタ //

GhostWalkGim::GhostWalkGim()
    :GhostBase()
    , isMove(false)
{
    objPos = VGet(120.0f, 0.0f, 65.0f);
    objSpeed = 17.0f;

    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, -40);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;
}

// デストラクタ //

GhostWalkGim::~GhostWalkGim()
{
}

// 更新処理 //

void GhostWalkGim::Update(float deltaTime)
{
    //アニメーション時間再生
    gstAnim->AddAnimTime(deltaTime);

    //動作中は移動
    if (isMove)
    {
        //当たり判定設定
        ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
        colLine = Line(VGet(7.0f, 5.0f, 0.0f), player->GetPos() - objPos + VGet(0, 5, 0));             //線分設定

        objPos.x -= objSpeed * deltaTime;
    }

    //モデル回転
    MV1SetPosition(objHandle, objPos);
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);

    //当たり判定更新
    ColUpdate();
}

// 描画処理 //

void GhostWalkGim::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}

// 衝突時処理 //

void GhostWalkGim::OnCollisionEnter(const ObjBase* other)
{
    ObjectTag tag = other->GetTag();

    //プレイヤーが一定距離近づいたら動作開始
    if (tag == ObjectTag::Player)
    {
        if (CollisionPair(colSphere, other->GetColSphere()))
        {
            //幽霊を歩かせる
            if (animType != WALK)
            {
                animType = WALK;
                gstAnim->StartAnim(animType);
                gstSound->StartSound(SoundTag::GhostWalk, DX_PLAYTYPE_BACK);
                isMove = true;

                //ライトの位置変更
                ObjBase* light = ObjManager::GetFirstObj(ObjectTag::Light);
                if (light)
                {
                    light->SetPos(VGet(-32, 33, 75));
                }

                ////ドア追加(開かせる)
                //class Door* door = new Door(VGet(0, 0, 66), VGet(-1, 0, 0));
                //ObjManager::Entry(door);
                //door->MoveAnim(Door::AnimType::OPEN);
            }
        }
    }

    //自身とプレイヤー間の線分が建物にぶつかったら死亡する
    if (tag == ObjectTag::Map ||
        tag == ObjectTag::Furniture)
    {
        int mapColModel = other->GetColModel();
        MV1_COLL_RESULT_POLY colInfoLine;
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