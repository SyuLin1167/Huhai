#include "Enemy.h"


/* @brief Enemyコンストラクタ */

Enemy::Enemy()
    :ObjectBase(ObjectTag::Enemy)
    ,emyAnim(nullptr)
    ,animType(IDLE)
{
    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Enemy/unityChanModel.mv1");        //モデル読み込み
    MV1SetScale(objHandle, VGet(0.01f, 0.01f, 0.01f));                             //モデルのサイズ設定
    
    emyAnim = new Animation(objHandle);                                         //アニメーションのインスタンス
   
    //---アニメーション読み込み---//
    emyAnim->AddAnimation("../SourceCode/Assets/Enemy/unityChanAnimIdle.mv1");      //待機:0
    emyAnim->AddAnimation("../SourceCode/Assets/Enemy/unityChanAnimRun.mv1");       //走る:1
    emyAnim->AddAnimation("../SourceCode/Assets/Enemy/unityChanAnimPunch.mv1");     //攻撃:2

    //---アニメーション状態セット---//
    emyAnim->StartAnim(animType);
    objDir = VGet(-1.0f, 0.0f, 0.0f);                                           //初期方向
    objPos = VGet(50.0f, 0.0f, 0.0f);                                           //初期位置
    MV1SetPosition(objHandle, objPos);                                          //ポジション設定

    //---当たり判定球設定---//
    colSphere.localCenter = VGet(0, 10, 0);			//ローカル座標
    colSphere.Radius = 5.0f;						//球半径
    colSphere.worldCenter = objPos;					//ワールド座標

    objSpeed = 5.0f;
}

// @brief Enemyデストラクター //

Enemy::~Enemy()
{
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
}

// @brief Enemy更新処理 //

void Enemy::Update(float deltaTime)
{
    Move(deltaTime);
    MV1SetPosition(objHandle, objPos);                        //ポジション設定
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));       //左向きに回転させる
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);         //モデル回転

    colSphere.Move(objPos);					//当たり判定の移動
}

// @brief Enemy描画処理 //

void Enemy::Draw()
{
    MV1DrawModel(objHandle);


    //---当たり判定デバッグ描画(後で消す)---//
    DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
}

void Enemy::Move(float deltaTime)
{
    objPos += objDir * objSpeed * deltaTime;                //移動
    if (animType != RUN)
    {
        animType = RUN;
        emyAnim->StartAnim(animType);
    }
}