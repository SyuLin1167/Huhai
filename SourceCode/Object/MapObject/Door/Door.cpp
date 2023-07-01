#include "Door.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Sound/Sound.h"

// コンストラクタ //

Door::Door()
    :ObjBase(ObjectTag::Furniture)
    , doorAnim(nullptr)
    , doorSound(nullptr)
{
    Load();
}

// コンストラクタ //

Door::Door(VECTOR doorPos, VECTOR doorAngle)
    :ObjBase(ObjectTag::Furniture, doorPos, doorAngle)
    , doorAnim(nullptr)
    , doorSound(nullptr)
{
    Load();
}

// デストラクタ //

Door::~Door()
{
    //インスタンス削除
    delete doorAnim;
    delete doorSound;
}

// 読み込み処理 //

void Door::Load()
{
    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Door/Door.mv1");
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));

    //アニメーション設定
    doorAnim = new Animation(objHandle);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorOpen.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    animType = IDLE;
    doorAnim->StartAnim(animType);
    doorAnim->StopAnim();

    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;

    //サウンド設定
    doorSound = new Sound;
    doorSound->AddSound("../Assets/Sound/DoorOpenSE.wav", SoundTag::DoorOpen, true);
    doorSound->AddSound("../Assets/Sound/DoorCloseSE.wav", SoundTag::DoorClose, true);
}

// 更新処理 //

void Door::Update(float deltaTime)
{
    //アニメーション時間再生
    doorAnim->AddAnimTime(deltaTime);

    //ドアの開閉処理
    player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        //プレイヤーが一定距離近づいていたら
        if (CollisionPair(colSphere, player->GetColSphere()))
        {
            if (!doorAnim->IsPlaying())
            {
                //Eキー入力でドア開放
                if (CheckHitKey(KEY_INPUT_E))
                {
                    if (animType != OPEN)
                    {
                        MoveAnim(OPEN);
                    }
                }
                //Qキー入力でドア閉鎖
                if (CheckHitKey(KEY_INPUT_Q))
                {
                    if (animType != CLOSE)
                    {
                        MoveAnim(CLOSE);
                    }
                }
            }

        }
    }

    //当たり判定更新
    colModel = objHandle;
    ColUpdate();

    //サウンド更新
    doorSound->Doppler(SoundTag::DoorOpen, objPos);
    doorSound->Doppler(SoundTag::DoorClose, objPos);
}

// アニメーション処理 //

void Door::MoveAnim(int animtype)
{
    //指定したアニメーションを再生する
    if (animType != animtype)
    {
        animType = animtype;
        doorAnim->StartAnim(animType);
        if (animtype == OPEN)
        {
            doorSound->StartSound(SoundTag::DoorOpen, DX_PLAYTYPE_BACK);
        }
        else if (animtype == CLOSE)
        {
            doorSound->StartSound(SoundTag::DoorClose, DX_PLAYTYPE_BACK);
        }
    }
}

// 描画処理 //

void Door::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}