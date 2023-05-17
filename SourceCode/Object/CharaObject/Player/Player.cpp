#include "Player.h"

// @brief Playerコンストラクター //

Player::Player()
    :ObjectBase(ObjectTag::Player)
    , inputVec{ 0,0,0 }
    , UP{ 0,0,0 }
    , DOWN{ 0,0,0 }
    , LEFT{ 0,0,0 }
    , RIGHT{ 0,0,0 }
    , inputVel{ 0,0,0 }
    , inputKey(false)
    , nowRoted(false)
    , camFront{ 0,0,0 }
{

    //---インスタンス---//

    objPos = { 0,0,0 };

    //---当たり判定球設定---//
    colType = CollisionType::Sphere;                                                        //当たり判定は球体
    colSphere.localCenter = VGet(0, 5, 0);                                                  //ローカル座標
    colSphere.Radius = 3.0f;                                                                //球半径
    colSphere.worldCenter = objPos;                                                         //ワールド座標

    //---当たり判定線分設定---//
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -3.0f, 0.0f));             //線分設定

}

// @brief Playerデストラクター //

Player::~Player()
{

}

//@brief Player更新処理//

void Player::Update(float deltaTime)
{
    ObjectBase* camFps = ObjManager::GetFirstObj(ObjectTag::Camera);
    camFront = camFps->GetDir();               //カメラの正面方向の位置ベクトルを計算
    camFront.y = 0;
    camFront = VNorm(camFront);               //ベクトルを正規化

    UP = camFront;                               //カメラ方向に前進
    DOWN = VScale(UP, -1.0f);              //カメラ方向から後進
    RIGHT = VCross(VGet(0, 1, 0), camFront);     //カメラ方向から右に前進
    LEFT = VScale(RIGHT, -1.0f);                    //カメラ方向から左に前進

    objDir = camFront;
    Move(deltaTime);                                        //Player移動処理

    objPos.y = 0;
    MV1SetPosition(objHandle, objPos);                              //ポジションセット

    colSphere.Move(objPos);                                         //当たり判定の移動
    ColUpdate();
}

// @brief Player描画処理 //

void Player::Draw()
{
    ColDraw();
}

// @brief Player衝突時処理 //

void Player::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();

    if (tag == ObjectTag::Map||
        tag == ObjectTag::Furniture)                                      //マップとぶつかったら
    {
        int mapColModel = other->GetColModel();                        //モデル当たり判定取得
        CollHitSphere(mapColModel);
        ColHitLine(mapColModel);
    }
}

// @brief 球体の衝突時処理 //

void Player::CollHitSphere(int colmodel)
{
    //---マップと境界球との当たり判定---//
    MV1_COLL_RESULT_POLY_DIM colInfo;                          //モデル当たり判定情報
    if (CollisionPair(colSphere, colmodel, colInfo))
    {
        VECTOR pushBack = CalcSpherePushBackFromMesh(colSphere, colInfo);   //押し戻し量算出
        objPos += pushBack;                                                         //押し戻す
        MV1CollResultPolyDimTerminate(colInfo);                        //当たり判定情報解放
        ColUpdate();
    }

}

// @brief 線分の衝突時処理 //

void Player::ColHitLine(int colmodel)
{
    //---マップと足元線分の当たり判定---//
    MV1_COLL_RESULT_POLY colInfoLine;                           //線分当たり判定情報
    if (CollisionPair(colLine, colmodel, colInfoLine))
    {
        objPos = colInfoLine.HitPosition;                       //足元を衝突時の座標に合わせる
        ColUpdate();
    }
}

// @brief Player移動処理 //

void Player::Move(float deltaTime)
{
    //---キー入力判定処理---//
    inputKey = false;                               //未入力時は入力判定をFALSEに

    if (CheckHitKey(KEY_INPUT_A))                //左キー入力
    {
        inputVec += LEFT;                           //ベクトル加算
        inputKey = true;                            //入力判定をTRUEに
    }
    if (CheckHitKey(KEY_INPUT_D))               //右キー入力
    {
        inputVec += RIGHT;
        inputKey = true;
    }
    if (CheckHitKey(KEY_INPUT_W))                  //上キー入力
    {
        inputVec += UP;
        inputKey = true;
    }
    if (CheckHitKey(KEY_INPUT_S))                //下キー入力
    {
        inputVec += DOWN;
        inputKey = true;
    }


    //---移動処理---//
    if (inputKey)                                                   //移動キーが入力されたら
    {

        inputVec = VNorm(inputVec);                                 //ベクトルの方向成分を取得
        
        if (VSquareSize(inputVec)==0)                               //左右・上下同時押しの際は無視
        {
            return;
        }

        inputVel = inputVec * objSpeed * deltaTime;                  //移動速度設定
    }
    else
    {
        inputVel *= 0.5f;                                           //徐々に減速
    }
    objPos += inputVel;                                             //移動
}
