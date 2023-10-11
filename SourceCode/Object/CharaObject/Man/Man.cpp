#include "Man.h"

#include "../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../UI/Action/Action.h"
#include"../../../UI/Reamarks/Remarks.h"
#include"../../../Asset/Sound/Sound.h"

/// <summary>
/// コンストラクタ
/// </summary>
Man::Man()
    :ObjBase(ObjTag::Man)
    , isSpeak(false)
    , manAnim(new Animation(objHandle))
    , manSound(new Sound)
{
    Load();
}

// デストラクタ //

Man::~Man()
{
}

// 読み込み処理 //

void Man::Load()
{
    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Chara/Man/ManModel.mv1");
    objPos = { -55.0f,0.0f,30.0f };
    objDir = { 0,0,-1 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.02f, 0.02f, 0.02f));

    //アニメーション設定
    manAnim->AddAnimation("../Assets/Chara/Man/ManCrying.mv1");
    manAnim->AddAnimation("../Assets/Chara/Man/ManDying.mv1", 30.0f, false);
    animType = CRYING;
    manAnim->StartAnim(animType);

    //サウンド設定
    manSound->AddSound("../Assets/Sound/ManHurtSE.mp3", SoundTag::ManHurt, true);
    manSound->AddSound("../Assets/Sound/BodyFallSE.mp3", SoundTag::BodyFall, true);

    //アクションボタン生成
    ObjManager::AddObj(new Action(objPos + VGet(0, 0, 5)));
}

// 更新処理 //

void Man::Update(float deltaTime)
{
    //アニメーション時間再生
    manAnim->AddAnimTime(deltaTime);

    //モデルの回転
    MATRIX rotYMat = MGetRotY(ONE_HALF_PI * (float)(DX_PI / ONE_HALF_PI));
    VECTOR negativeVec = VTransform(objDir, rotYMat);

    //アクションボタンが押されたらセリフを再生
    if (!ObjManager::GetObj(ObjTag::UI, 3)->IsVisible())
    {
        //プレイヤーの方を向く
        rotateNow = true;
        aimDir = VSub(ObjManager::GetFirstObj(ObjTag::Player)->GetPos(), objPos);
        aimDir = VNorm(aimDir);
        Rotate();

        //セリフが終わったら男性を死亡させる
        ObjBase* remarks = ObjManager::GetFirstObj(ObjTag::Remarks);
        if (!remarks && isSpeak)
        {
            if (animType != DEAD)
            {
                animType = DEAD;
                manAnim->StartAnim(animType);
                manSound->StartSound(SoundTag::ManHurt, DX_PLAYTYPE_BACK);
            }
            if (!manSound->IsPlaying(SoundTag::ManHurt))
            {
                manSound->StartSound(SoundTag::BodyFall, DX_PLAYTYPE_BACK);
            }
        }
        if (animType == DEAD && !manAnim->IsPlaying())
        {
            isAlive = false;
        }

        //向き終わったら会話中にする
        if (!rotateNow && !isSpeak)
        {
            ObjManager::AddObj(new Remarks(TextType::ManSpeak));
            isSpeak = true;
        }
    }

    // モデルに回転をセットする
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    //サウンド更新
    manSound->Doppler(SoundTag::ManHurt,objPos);
    manSound->Doppler(SoundTag::BodyFall, objPos);
}

// 描画処理 //

void Man::Draw()
{
    MV1DrawModel(objHandle);
}