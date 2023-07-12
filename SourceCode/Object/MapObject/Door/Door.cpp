#include "Door.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Sound/Sound.h"
#include"../../../UI/Action/Action.h"

// コンストラクタ //

Door::Door(VECTOR pos, VECTOR angle)
    :ObjBase(ObjectTag::Furniture, pos, angle)
    , doorAnim(nullptr)
    , animType(IDLE)
    , doorSound(nullptr)
    , rotateNow(true)
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

    //アニメーション設定
    doorAnim = new Animation(objHandle);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorOpen.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->StartAnim(animType);
    doorAnim->StopAnim();

    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;

    //サウンド設定
    doorSound = new Sound;
    doorSound->AddSound("../Assets/Sound/DoorOpenSE.wav", SoundTag::DoorOpen, true, true);
    doorSound->AddSound("../Assets/Sound/DoorCloseSE.wav", SoundTag::DoorClose, true, true);

    //アクションボタン追加
    action = new Action(objPos);
    ObjManager::Entry(action);
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
        //プレイヤーが近づいたらボタン表示
        VECTOR actionPos = player->GetPos() - objPos;
        actionPos = VNorm(actionPos);
        action->SetPos(objPos + actionPos + VGet(0, 20, 0));

        if (!doorAnim->IsPlaying())
        {

            //Eキー入力でドア開放
            if (!action->IsVisible())
            {
                if (animType != OPEN)
                {
                    MoveAnim(OPEN);
                }
            }
            //Qキー入力でドア閉鎖
            if (CheckHitKey(KEY_INPUT_Q))
            {
                if (animType == OPEN)
                {
                    MoveAnim(CLOSE);
                }
            }
        }
    }

    //モデルの回転
    MATRIX rotYMat = MGetRotY(90.0f * (float)(DX_PI / 180.0f));
    VECTOR negativeVec = VTransform(objDir, rotYMat);
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

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
            action->SetVisible(false);
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