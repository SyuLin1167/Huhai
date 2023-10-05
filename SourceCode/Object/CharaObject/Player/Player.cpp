#include "Player.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Scene/PauseMenu/PauseMenu.h"
#include"../../../Asset/Sound/Sound.h"

// コンストラクタ //

Player::Player()
    :ObjBase(ObjectTag::Player)
    , canMove(true)
    , UP(VGet(0,0,0))
    , DOWN(VGet(0,0,0))
    , LEFT(VGet(0,0,0))
    , RIGHT(VGet(0,0,0))
    , inputVec(VGet(0,0,0))
    , inputVel(VGet(0,0,0))
    , walkStep(0.0f)
    , inputKey(false)
    , camFront(VGet(0,0,0))
    , plySound(nullptr)
{
    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5.0f, 0);
    colSphere.Radius = 3.0f;
    colSphere.worldCenter = objPos;
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -3.0f, 0.0f));

    //サウンド設定
    plySound = new Sound;
    plySound->AddSound("../Assets/Sound/PlayerWalkSE.mp3", SoundTag::PlayerWalk, false, true);
}

// デストラクタ //

Player::~Player()
{
}

// 更新処理 //

void Player::Update(float deltaTime)
{
    //カメラの向き取得
    ObjBase* camFps = ObjManager::GetFirstObj(ObjectTag::Camera);
    camFront = camFps->GetDir();
    camFront.y = 0;
    camFront = VNorm(camFront);

    //移動時のカメラの上下運動
    if (PauseMenu::HasStatus("Camera"))
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
    UP = camFront;
    DOWN = VScale(UP, -1.0f);
    RIGHT = VCross(VGet(0, 1, 0), camFront);
    LEFT = VScale(RIGHT, -1.0f);
    objDir = camFront;

    //動作中は操作可能
    if (canMove)
    {
        Move(deltaTime);
    }

    //セリフ表示時は動作停止
    if (ObjManager::GetFirstObj(ObjectTag::Remarks))
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

// 描画処理 //

void Player::Draw()
{
}

// 衝突時処理 //

void Player::OnCollisionEnter(const ObjBase* other)
{
    ObjectTag tag = other->GetTag();

    //建物にぶつかったら押し戻す
    if (tag == ObjectTag::Map ||
        tag == ObjectTag::Furniture)
    {
        int mapColModel = other->GetColModel();
        CollHitSphere(mapColModel);
        ColHitLine(mapColModel);
    }

    //幽霊にぶつかったら死亡
    if (tag == ObjectTag::Ghost)
    {
        if (abs(VSize(other->GetPos() - objPos)) < 12.0f && canMove)
        {
            canMove = false;
            isVisible = false;
            ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
            if (camera)
            {
                camera->SetDir(other->GetPos() - camera->GetPos() + VGet(0, 18.0f, 0));
            }
        }
        ColUpdate();
    }
}

// 球体の衝突時処理 //

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

// 線分の衝突時処理 //

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

// 移動処理 //

void Player::Move(float deltaTime)
{
    //通常は未入力
    inputKey = false;

    //Aキー入力で左に移動
    if (CheckHitKey(KEY_INPUT_A))
    {
        inputVec += LEFT;
        inputKey = true;
    }
    //Dキー入力で右に移動
    if (CheckHitKey(KEY_INPUT_D))
    {
        inputVec += RIGHT;
        inputKey = true;
    }
    //Wキー入力で前に移動
    if (CheckHitKey(KEY_INPUT_W))
    {
        inputVec += UP;
        inputKey = true;
    }
    //Sキー入力で後ろに移動
    if (CheckHitKey(KEY_INPUT_S))
    {
        inputVec += DOWN;
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