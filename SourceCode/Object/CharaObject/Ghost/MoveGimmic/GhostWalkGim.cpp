#include "GhostWalkGim.h"

#include"../../../MapObject/Light/NomalLight/NomalLight.h"
#include"../../../MapObject/Door/Door.h"
#include"../../Man/Man.h"

GhostWalkGim::GhostWalkGim()
    :GhostBase()
{
    objPos = VGet(120.0f, 0.0f, 65.0f);
    objSpeed = 17.0f;

    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, -40);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;
}

GhostWalkGim::~GhostWalkGim()
{
    //処理なし
}

void GhostWalkGim::Update(const float deltaTime)
{
    //アニメーション時間再生
    ghostAnim->AddAnimTime(deltaTime);

    //動作中は移動
    if (isMove)
    {
        //当たり判定設定
        ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
        colLine = Line(COL_LINE_FIRST_POS+COL_LINE_HEIGHT,
            player->GetPos() - objPos + COL_LINE_HEIGHT);

        objPos.x -= objSpeed * deltaTime;
    }

    //モデル回転
    MV1SetPosition(objHandle, objPos);
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);

    //当たり判定更新
    ColUpdate();
}

void GhostWalkGim::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}

void GhostWalkGim::OnCollisionEnter(const ObjBase* other)
{
    ObjTag tag = other->GetTag();

    //プレイヤーが一定距離近づいたら動作開始
    if (tag == ObjTag::Player)
    {
        if (CollisionPair(colSphere, other->GetColSphere()))
        {
            //幽霊を歩かせる
            if (animType != WALK)
            {
                animType = WALK;
                ghostAnim->StartAnim(animType);
                ghostSound->StartSound(SoundTag::GhostWalk, DX_PLAYTYPE_BACK);
                isMove = true;
            }
        }
    }

    //自身とプレイヤー間の線分が建物にぶつかったら死亡する
    if (tag == ObjTag::Map ||
        tag == ObjTag::Furniture)
    {
        int mapColModel = other->GetColModel();
        MV1_COLL_RESULT_POLY colInfoLine;
        if (CollisionPair(colLine, mapColModel, colInfoLine))
        {
            isVisible = false;
            if (!ghostSound->IsPlaying(SoundTag::GhostWalk))
            {
                isAlive = false;
            }
            ColUpdate();
        }
    }
}