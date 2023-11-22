#include "Player.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Scene/PauseScene/PauseMenu/PauseMenu.h"
#include"../../../Asset/Sound/Sound.h"

Player::Player()
    :ObjBase(ObjTag::Player)
    , canMove(true)
    , Up(VGet(0,0,0))
    , Down(VGet(0,0,0))
    , Left(VGet(0,0,0))
    , Right(VGet(0,0,0))
    , inputVec(VGet(0,0,0))
    , inputVel(VGet(0,0,0))
    , walkStep(0.0f)
    , inputKey(false)
    , camFront(VGet(0,0,0))
    , plySound(new Sound)
{
    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5.0f, 0);
    colSphere.Radius = 3.0f;
    colSphere.worldCenter = objPos;
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -3.0f, 0.0f));

    //サウンド設定
    plySound->AddSound("../Assets/Sound/PlayerWalkSE.mp3", SoundTag::PlayerWalk, false, true);
}

Player::~Player()
{
    //処理なし
}

void Player::Update(const float deltaTime)
{
    //カメラの向き取得
    ObjBase* camFps = ObjManager::GetFirstObj(ObjTag::Camera);
    camFront = camFps->GetDir();
    camFront.y = 0;
    camFront = VNorm(camFront);

    //移動時のカメラの上下運動
    ButtonName buttonName;
    if (PauseMenu::HasStatus(buttonName.camera))
    {
        if (inputKey)
        {
            if (walkStep < DX_PI_F)
            {
                walkStep += 5.0f * deltaTime;
            }
            else
            {
                walkStep = 0;
            }
            camFps->SetPos(VGet(objPos.x, camFps->GetPos().y + sin(walkStep), objPos.z));
        }
    }

    //カメラの向きに合わせて移動方向決定
    Up = camFront;
    Down = VScale(Up, -1.0f);
    Right = VCross(VGet(0, 1, 0), camFront);
    Left = VScale(Right, -1.0f);
    objDir = camFront;

    //動作中は操作可能
    if (canMove)
    {
        Move(deltaTime);
    }

    //セリフ表示時は動作停止
    if (ObjManager::GetFirstObj(ObjTag::Remarks))
    {
        canMove = false;
    }
    else
    {
        canMove = true;
    }

    //当たり判定更新
    ColUpdate();
}

void Player::Draw()
{
    //処理なし
}

/// <summary>
/// 当たり判定処理
/// </summary>
/// <param name="other">:オブジェクト</param>
void Player::OnCollisionEnter(const ObjBase* other)
{
    ObjTag tag = other->GetTag();

    //建物にぶつかったら押し戻す
    if (tag == ObjTag::Map ||
        tag == ObjTag::Furniture)
    {
        int mapColModel = other->GetColModel();
        CollHitSphere(mapColModel);
        ColHitLine(mapColModel);
    }

    //幽霊にぶつかったら死亡
    if (tag == ObjTag::Ghost)
    {
        if (abs(VSize(other->GetPos() - objPos)) < HIT_DISTANCE && canMove)
        {
            canMove = false;
            isVisible = false;
            ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
            if (camera)
            {
                camera->SetDir(other->GetPos() - camera->GetPos() + HIT_AIM_POS);
            }
        }
        ColUpdate();
    }
}

void Player::CollHitSphere(int colmodel)
{
    //球体がモデルの当たったら押し戻す
    MV1_COLL_RESULT_POLY_DIM colInfo;
    if (CollisionPair(colSphere, colmodel, colInfo))
    {
        VECTOR pushBack = CalcSpherePushBackFromMesh(colSphere, colInfo);
        objPos += pushBack;
        MV1CollResultPolyDimTerminate(colInfo);
        ColUpdate();
    }

}

void Player::ColHitLine(int colmodel)
{
    //線分がモデルに当たったら足元の座標に合わせる
    MV1_COLL_RESULT_POLY colInfoLine;
    if (CollisionPair(colLine, colmodel, colInfoLine))
    {
        objPos = colInfoLine.HitPosition;
        ColUpdate();
    }
}

void Player::Move(float deltaTime)
{
    //通常は未入力
    inputKey = false;

    //Aキー入力で左に移動
    if (CheckHitKey(KEY_INPUT_A))
    {
        inputVec += Left;
        inputKey = true;
    }
    //Dキー入力で右に移動
    if (CheckHitKey(KEY_INPUT_D))
    {
        inputVec += Right;
        inputKey = true;
    }
    //Wキー入力で前に移動
    if (CheckHitKey(KEY_INPUT_W))
    {
        inputVec += Up;
        inputKey = true;
    }
    //Sキー入力で後ろに移動
    if (CheckHitKey(KEY_INPUT_S))
    {
        inputVec += Down;
        inputKey = true;
    }

    //キー入力中は移動
    if (inputKey)
    {
        plySound->StartSound(SoundTag::PlayerWalk, DX_PLAYTYPE_LOOP);
        inputVec = VNorm(inputVec);
        if (VSquareSize(inputVec) == 0)
        {
            return;
        }
        inputVel = inputVec * objSpeed * deltaTime;
    }
    else
    {
        //未入力時は移動停止
        plySound->StopSound(SoundTag::PlayerWalk);
        inputVel *= 0.0f;
    }
    objPos += inputVel;
}