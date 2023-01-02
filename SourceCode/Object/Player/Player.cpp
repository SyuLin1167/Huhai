#include "Player.h"

// @brief Playerコンストラクター //

Player::Player()
    :ObjectBase(ObjectTag::Player)
    , plyAnim(nullptr)
    , animType(IDLE)
    , UP{ 0,0,0 }
    , DOWN{ 0,0,0 }
    , RIGHT{ 0,0,0 }
    , LEFT{ 0,0,0 }
    , inputVec{ 0,0,0 }
    , inputVel{ 0,0,0 }
    , aimDir{ 0,0,0 }
    , inputKey(false)
    , nowRoted(false)
    , camFront{ 0,0,0 }
{
    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Player/PlayerModel.mv1");       //モデル読み込み
    MV1SetScale(objHandle, objScale);                                         //モデルのサイズ設定

    plyAnim = new Animation(objHandle);                                                     //アニメーションのインスタンス
    plyCol = new Collision();

    //---アニメーション読み込み---//
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Idle.mv1");              //待機:0
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Run.mv1");               //走る:1
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Atack.mv1", false);      //攻撃:2

    //---アニメーション状態セット---//
    plyAnim->StartAnim(animType);                       //待機モーションでアニメーション開始
    objDir = VGet(0, 0, 1);                //初期方向

    //---当たり判定球設定---//
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 6, 0);			//ローカル座標
    colSphere.Radius = 5.0f;						//球半径
    colSphere.worldCenter = objPos;					//ワールド座標

    //---当たり判定線分設定---//
    colLine = Collision::Line(VGet(0.0f, 2.0f,0.0f), VGet(0.0f, -3.0f, 0.0f));

}

// @brief Playerデストラクター //

Player::~Player()
{
    
    delete plyAnim;                                 //アニメーション解放
}

//@brief Player更新処理//

void Player::Update(float deltaTime)
{
    ObjectBase* camFps = ObjManager::GetFirstObj(ObjectTag::Camera);

    plyAnim->AddAnimTime(deltaTime);                //現在のアニメーション再生を進める

    camFront = objPos - camFps->GetPos();               //カメラの正面方向の位置ベクトルを計算
    camFront.y = 0;
    camFront = VNorm(camFront);               //ベクトルを正規化

    UP = camFront;                               //カメラ方向に前進
    DOWN = VScale(UP, -1.0f);              //カメラ後方に前進
    RIGHT = VCross(VGet(0, 1, 0), camFront);     //カメラ右方向に前進
    LEFT = VScale(RIGHT, -1.0f);                    //カメラ左方向

    Rotate();                                               //Player回転処理
    Move(deltaTime);                                        //Player移動処理

    MV1SetPosition(objHandle, objPos);                              //ポジションセット

    //---モデル回転処理---//
    MATRIX RotMatY = MGetRotY(180.0f * (float)(DX_PI / 180.0f));    //モデル反転行列
    VECTOR negativeVec = VTransform(objDir, RotMatY);               //負のベクトル
    MV1SetRotationZYAxis(objHandle, negativeVec,
    VGet(0.0f, 1.0f, 0.0f), 0.0f);                                  //モデル回転

    colSphere.Move(objPos);                                         //当たり判定の移動
    ColUpdate();
}

// @brief Player描画処理 //

void Player::Draw()
{
    MV1DrawModel(objHandle);                                        //モデル描画
    ColDraw();
    //---当たり判定デバッグ描画(後で消す)---//
    DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
}

// @brief Player衝突時処理 //

void Player::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();

    if (tag == ObjectTag::Map)                                      //マップとぶつかったら
    {
        int colModel = other->GetColModel();                        //モデル当たり判定取得

        //---マップと境界球都の当たり判定---//
        MV1_COLL_RESULT_POLY_DIM colInfo;                          //モデル当たり判定情報
        if (plyCol->CollisionPair(colSphere, colModel, colInfo))
        {
            VECTOR pushBack = plyCol->CalcSpherePushBackFromMesh(colSphere, colInfo);   //押し戻し量算出
            objPos += pushBack;                                                         //押し戻す
            MV1CollResultPolyDimTerminate(colInfo);                        //当たり判定情報解放
            ColUpdate();
        }

        //---マップと足元線分の当たり判定---//
        MV1_COLL_RESULT_POLY colInfoLine;                           //線分当たり判定情報
        if (plyCol->CollisionPair(colLine, colModel, colInfoLine))
        {
            objPos = colInfoLine.HitPosition;                       //足元を衝突時の座標に合わせる
            ColUpdate();
        }
    }
}

// @brief Player移動処理 //

void Player::Move(float deltaTime)
{
    //---キー入力判定処理---//
    inputKey = false;                               //未入力時は入力判定をFALSEに

    if (CheckHitKey(KEY_INPUT_LEFT))                //左キー入力
    {
        inputVec += LEFT;                           //ベクトル加算
        inputKey = true;                            //入力判定をTRUEに
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))               //右キー入力
    {
        inputVec += RIGHT;
        inputKey = true;
    }
    if (CheckHitKey(KEY_INPUT_UP))                  //上キー入力
    {
        inputVec += UP;
        inputKey = true;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))                //下キー入力
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

        if (IsSameAngle(inputVec, objDir))                      //現在方向が入力方向と異なっていたら
        {
            objDir = inputVec;                                          //入力方向を取得
        }
        else
        {
            nowRoted = true;
            aimDir = inputVec;
        }

        inputVel = inputVec * objSpeed * deltaTime;                  //移動速度設定

        if (animType != RUN)                                        //アニメーションが走るモーションでなければ
        {
            animType = RUN;                                         //アニメーションは走るモーション
            plyAnim->StartAnim(RUN);                                //走るモーションでアニメーション開始
        }
    }
    else
    {
        inputVel *= 0.9f;                                           //徐々に減速
        if (animType != IDLE)                                       //アニメーションが待機モーションでなければ
        {
            animType = IDLE;                                        //アニメーションは待機モーション
            plyAnim->StartAnim(IDLE);                               //待機モーションでアニメーション開始
        }
    }
    objPos += inputVel;                                             //移動
}

// @brief Player回転処理 //

void Player::Rotate()
{
    if (nowRoted)                           //現在回転中だったら
    {
        if (IsSameAngle( objDir,aimDir))     //目標の角度に十分近づいていたら
        {
            objDir = aimDir;                        //角度を目標の角度にして
            nowRoted = false;                       //回転停止
        }
        else
        {
            VECTOR rotDir = RotForAimY(objDir, aimDir, 10.0f);     //回転中のベクトル

            VECTOR cross1 = VCross(objDir, aimDir);            //プレイヤーの角度と目標角の外積
            VECTOR cross2 = VCross(rotDir, aimDir);            //回転中の角度と目標角の外積

            if (cross1.y * cross2.y < 0.0f)                     //回転が目標角度を超えたら
            {
                rotDir = aimDir;                                //回転中の角度を目標の角度に設定
                nowRoted = false;                               //回転停止
            }
            
            objDir = rotDir;                                    // 目標角に10度近づけた角度
        }
    }
}