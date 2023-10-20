#include "Chair.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/Sound/Sound.h"

/// <summary>
/// コンストラクタ
/// </summary>
Chair::Chair()
    :ObjBase(ObjTag::Furniture)
    , chairSound(new Sound)
{
    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Chair/Chair.mv1");
    objPos = { 66,0,4 };
    objDir = { 0,-90,0 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / PI_DEGREE * DX_PI_F, 0.0f));

    //アニメーション設定
    chairAnim.reset(new Animation(objHandle));
    chairAnim->AddAnimation("../Assets/Map/Chair/Chair.mv1");
    chairAnim->AddAnimation("../Assets/Map/Chair/ChairMove.mv1", 30.0f, false);
    animType = IDLE;
    chairAnim->StartAnim(animType);

    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;
    colModel = objHandle;

    //サウンド設定
    chairSound->AddSound("../Assets/Sound/MoveChairSE.mp3", SoundTag::MoveChair, true, true);
    chairSound->AddSound("../Assets/Sound/FallingChairSE.mp3", SoundTag::FallingChair, true, true);
}

/// <summary>
/// デストラクタ
/// </summary>
Chair::~Chair()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
void Chair::Update(const float deltaTime)
{
    //アニメーション時間再生
    chairAnim->AddAnimTime(deltaTime);

    //動作処理
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        //プレイヤーが一定距離近づいたら動作する
        if (CollisionPair(colSphere, player->GetColSphere()))
        {
            if (animType != MOVE)
            {
                animType = MOVE;
                chairAnim->StartAnim(animType);
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

/// <summary>
/// 描画処理
/// </summary>
void Chair::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}