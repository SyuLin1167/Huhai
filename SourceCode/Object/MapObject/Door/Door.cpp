#include "Door.h"
// @brief Doorコンストラクター //

Door::Door()
    :ObjectBase(ObjectTag::Furniture)
    ,doorAnim(nullptr)
    ,doorModel(nullptr)
{
    Load();
}

// @brief Doorコンストラクター //

Door::Door(VECTOR doorPos,VECTOR doorAngle)
    :ObjectBase(ObjectTag::Furniture,doorPos,doorAngle)
    ,doorAnim(nullptr)
    ,doorModel(nullptr)
{
    Load();
}

// @brief Doorデストラクター //

Door::~Door()
{
    delete doorAnim;
}

// @brief Door読み込み処理 //

void Door::Load()
{
    //---モデル読み込み---//
    objHandle=AssetManager::GetMesh("../Assets/Map/Door/Door.mv1");            //モデル読み込み

    MV1SetPosition(objHandle, objPos);                                                      //モデルの座標設定
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));                                                       //モデルのサイズ設定
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //モデルの向き設定

    //---アニメーション読み込み---//
    doorAnim = new Animation(objHandle);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);                        //待機:0
    doorAnim->AddAnimation("../Assets/Map/Door/DoorOpen.mv1", 30.0f, false);      //開:1
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);     //閉:2

    animType = IDLE;
    doorAnim->StartAnim(animType);
    doorAnim->StopAnim();

    colType = CollisionType::Sphere;                                                         //当たり判定は球体

    colSphere.localCenter = VGet(0, 5, 0);                                                 //ローカル座標
    colSphere.Radius = 15.0f;                                                                //球半径
    colSphere.worldCenter = objPos;                                                          //ワールド座標

}

// @brief Door更新処理 //

void Door::Update(float deltaTime)
{
    doorAnim->AddAnimTime(deltaTime);	

    //---当たり判定設定---//
    player = ObjManager::GetFirstObj(ObjectTag::Player);         //プレイヤーオブジェクト取得
    if (player)                                                              //オブジェクトの中身が空でなければ
    {
        if (CollisionPair(colSphere, player->GetColSphere()))
        {
            if (!doorAnim->IsPlaying())
            {
                if (CheckHitKey(KEY_INPUT_E))                //Eキー入力
                {
                    MoveAnim(OPEN);
                }
                if (CheckHitKey(KEY_INPUT_Q))                //Qキー入力
                {
                    MoveAnim(CLOSE);
                }
            }
        }
    }
    colModel = objHandle;                                           //当たり判定のモデルはオブジェクトのモデル
    ColUpdate();

}

// @brief Doorアニメーション処理

void Door::MoveAnim(int animtype)
{
    if (animType != animtype)															//現在のアニメーションが指定したアニメーションじゃなかったら
    {
        animType = animtype;														//現在のアニメーションを指定したアニメーションにする
        doorAnim->StartAnim(animType);												//アニメーション開始
    }
}

// @brief Door描画処理 //

void Door::Draw()
{
	MV1DrawModel(objHandle);						//モデル描画
}