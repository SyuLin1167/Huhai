#include "Chair.h"
#include"../../../Asset/Sound/Sound.h"

        // コンストラクタ //

Chair::Chair()
    :ObjectBase(ObjectTag::Furniture)
    , ChairAnim(nullptr)
    , chairSound(nullptr)
{
    Load();
}

        // デストラクタ //

Chair::~Chair()
{
    AssetManager::ReleaseMesh(objHandle);
    delete ChairAnim;
    delete chairSound;
}

        // 読み込み処理 //

void Chair::Load()
{
    objPos = { 66,0,4 };
    objDir = { 0,-90,0 };

    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../Assets/Map/Chair/Chair.mv1");            //モデル読み込み

    MV1SetPosition(objHandle, objPos);                                                      //モデルの座標設定
    MV1SetScale(objHandle, objScale);                                                       //モデルのサイズ設定
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //モデルの向き設定

    //---インスタンス---//
    ChairAnim = new Animation(objHandle);

    //---アニメーション読み込み---//
    ChairAnim->AddAnimation("../Assets/Map/Chair/Chair.mv1");                        //待機:0
    ChairAnim->AddAnimation("../Assets/Map/Chair/ChairMove.mv1", 30.0f, false);      //動く:1

    animType = IDLE;
    ChairAnim->StartAnim(animType);

    //---当たり判定---//
    colType = CollisionType::Sphere;                                                         //当たり判定は球体

    colSphere.localCenter = VGet(0, 5, 0);                                                 //ローカル座標
    colSphere.Radius = 15.0f;                                                                //球半径
    colSphere.worldCenter = objPos;                                                          //ワールド座標

    chairSound = new Sound;
    chairSound->AddSound("../Assets/Sound/MoveChairSE.mp3", SoundTag::MoveChair, 300, true);
    chairSound->AddSound("../Assets/Sound/FallingChairSE.mp3", SoundTag::FallingChair, 150, true);
}

        // 更新処理 //

void Chair::Update(float deltaTime)
{
    ChairAnim->AddAnimTime(deltaTime);
    chairSound->Update(objPos);

    //---当たり判定設定---//
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);         //プレイヤーオブジェクト取得
    if (player)                                                              //オブジェクトの中身が空でなければ
    {
        if (CollisionPair(colSphere, player->GetColSphere()))
        {
            if (animType != MOVE || animType == IDLE)                                       //アニメーション開くモーションでなければ
            {
                animType = MOVE;                                        //アニメーションは開くモーション
                ChairAnim->StartAnim(animType);                               //開くモーションでアニメーション開始
                chairSound->StartSoundOnce(SoundTag::MoveChair, DX_PLAYTYPE_BACK);
            }
        }
    }

    colModel = objHandle;																//当たり判定のモデルはオブジェクトのモデル
    ColUpdate();

}

        // 描画処理 //

void Chair::Draw()
{
    MV1DrawModel(objHandle);						//モデル描画
}