#include "Chair.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/Sound/Sound.h"

// コンストラクタ //

Chair::Chair()
    :ObjBase(ObjectTag::Furniture)
    , ChairAnim(nullptr)
    , chairSound(nullptr)
{
    Load();
}

// デストラクタ //

Chair::~Chair()
{
    //インスタンス削除
    delete ChairAnim;
    delete chairSound;
}

// 読み込み処理 //

void Chair::Load()
{

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Chair/Chair.mv1");
    objPos = { 66,0,4 };
    objDir = { 0,-90,0 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));

    //アニメーション設定
    ChairAnim = new Animation(objHandle);
    ChairAnim->AddAnimation("../Assets/Map/Chair/Chair.mv1");
    ChairAnim->AddAnimation("../Assets/Map/Chair/ChairMove.mv1", 30.0f, false);
    animType = IDLE;
    ChairAnim->StartAnim(animType);

    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;
    colModel = objHandle;

    //サウンド設定
    chairSound = new Sound;
    chairSound->AddSound("../Assets/Sound/MoveChairSE.mp3", SoundTag::MoveChair, true, true);
    chairSound->AddSound("../Assets/Sound/FallingChairSE.mp3", SoundTag::FallingChair, true, true);
}

        // 更新処理 //

void Chair::Update(float deltaTime)
{
    //アニメーション時間再生
    ChairAnim->AddAnimTime(deltaTime);

    //動作処理
    ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        //プレイヤーが一定距離近づいたら動作する
        if (CollisionPair(colSphere, player->GetColSphere()))
        {
            if (animType != MOVE)
            {
                animType = MOVE;
                ChairAnim->StartAnim(animType);
                colModel = -1;
                chairSound->StartSoundOnce(SoundTag::MoveChair, DX_PLAYTYPE_BACK);
            }
        }
    }

    //当たり判定更新
    ColUpdate();

    //サウンド更新
    chairSound->Doppler(SoundTag::MoveChair,objPos);
    chairSound->Doppler(SoundTag::FallingChair, objPos);
}

// 描画処理 //

void Chair::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}