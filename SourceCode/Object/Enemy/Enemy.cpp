#include "Enemy.h"


/* @brief Enemyコンストラクタ */

Enemy::Enemy()
    :ObjectBase(ObjectTag::Enemy)
{
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Enemy/SampleEnemy.MV1");        //モデル読み込み
    MV1SetScale(objHandle, VGet(0.1f, 0.1f, 0.1f));                             //モデルのサイズ設定
    objDir = VGet(-1.0f, 0.0f, 0.0f);                                           //初期方向
    objPos = VGet(10.0f, 0.0f, 0.0f);                                           //初期位置
    MV1SetPosition(objHandle, objPos);                                          //ポジション設定

    objSpeed = 5.0f;

    //---当たり判定球設定---//
    colSphere.localCenter = VGet(0, 10, 0);			//ローカル座標
    colSphere.Radius = 5.0f;						//球半径
    colSphere.worldCenter = objPos;					//ワールド座標
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
    objPos += objDir * objSpeed * deltaTime;                //移動
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

