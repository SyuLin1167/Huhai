#include "Player.h"

// @brief Playerコンストラクター //

Player::Player()
    :ObjectBase(ObjectTag::Player)
    ,UP{0,0,0}
    ,DOWN{0,0,0}
    ,RIGHT{0,0,0}
    ,LEFT{0,0,0}
    , InputVec{0,0,0}
    , KeyInput(false)
    ,plyAnim(nullptr)
    , animType(IDLE)
    ,cameraPos{0,58,0}
    ,cameraFront{0,0,0}
    ,cameraRotSpeed(0.5f)
    ,cameraRad(-40.0f)
{
    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Player/PlayerModel.mv1");       //モデル読み込み
    MV1SetScale(objHandle, VGet(0.1f, 0.1f, 0.1f));                                         //モデルのサイズ設定

    plyAnim = new Animation(objHandle);                                                     //アニメーションのインスタンス

    //---アニメーション読み込み---//
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Idle.mv1");              //待機:0
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Run.mv1");               //走る:1
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Atack.mv1", false);      //攻撃:2

    //---アニメーション状態セット---//
    animType = IDLE;                                //アニメーションは待機モーション
    plyAnim->StartAnim(IDLE);                       //待機モーションでアニメーション開始
    objDir = VGet(0.0f, 0.0f, 1.0f);                //初期方向
    objSpeed = 5.0f;                                //初期速度

    //---当たり判定球設定---//
    colSphere.localCenter = VGet(0, 10, 0);			//ローカル座標
    colSphere.Radius = 5.0f;						//球半径
    colSphere.worldCenter = objPos;					//ワールド座標
}

// @brief Playerデストラクター //

Player::~Player()
{
    delete plyAnim;                                 //アニメーション解放
}

//@brief Player更新処理//

void Player::Update(float deltaTime)
{
    CameraUpdate(deltaTime);                        //カメラ更新

    plyAnim->AddAnimTime(deltaTime);                //現在のアニメーション再生を進める

    cameraFront = objPos - cameraPos;               //カメラの正面方向の位置ベクトルを計算
    cameraFront = VNorm(cameraFront);               //ベクトルを正規化

    UP = cameraFront;
    DOWN = VScale(cameraFront, -1.0f);
    RIGHT = VCross(VGet(0, 1, 0), cameraFront);
    LEFT = VScale(RIGHT, -1.0f);

    //---キー入力判定処理---//
    KeyInput = false;                               //未入力時は入力判定をFALSEに

    if (CheckHitKey(KEY_INPUT_LEFT))                //左キー入力
    {
        InputVec += LEFT;                           //ベクトル加算
        KeyInput = true;                            //入力判定をTRUEに
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))               //右キー入力
    {
        InputVec += RIGHT;
        KeyInput = true;
    }
    if (CheckHitKey(KEY_INPUT_UP))                  //上キー入力
    {
        InputVec += UP;
        KeyInput = true;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))                //下キー入力
    {
        InputVec += DOWN;
        KeyInput = true;
    }


    //---移動処理---//
    if (KeyInput)                                                   //移動キーが入力されたら
    {
        InputVec = VNorm(InputVec);                                 //ベクトルの方向成分を取得
        objDir = InputVec;                                          //キャラの向きを取得
        objPos += InputVec * objSpeed * deltaTime;                  //移動

        if (animType != RUN)                                        //アニメーションが走るモーションでなければ
        {
            animType = RUN;                                         //アニメーションは走るモーション
            plyAnim->StartAnim(RUN);                                //走るモーションでアニメーション開始
        }
    }
    else
    {
        if (animType != IDLE)                                       //アニメーションが待機モーションでなければ
        {
            animType = IDLE;                                        //アニメーションは待機モーション
            plyAnim->StartAnim(IDLE);                               //待機モーションでアニメーション開始
        }
    }
    MV1SetPosition(objHandle, objPos);                              //ポジションセット

    //---モデル回転処理---//
    MATRIX RotMatY = MGetRotY(180.0f * (float)(DX_PI / 180.0f));    //モデル反転行列
    VECTOR negativeVec = VTransform(objDir, RotMatY);               //負のベクトル
    MV1SetRotationZYAxis(objHandle, negativeVec,
    VGet(0.0f, 1.0f, 0.0f), 0.0f);                                  //モデル回転

    colSphere.Move(objPos);                                         //当たり判定の移動
}

// @brief Player描画処理 //

void Player::Draw()
{
    MV1DrawModel(objHandle);                                        //モデル描画

    //---当たり判定デバッグ描画(後で消す)---//
    DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
}

// @brief Camera更新処理 //

void Player::CameraUpdate(float deltaTime)
{
    if (CheckHitKey(KEY_INPUT_Q))                                   //Qキーが押されたら
    {
        cameraYaw -= cameraRotSpeed * deltaTime;                    //回転角は負の方向
    }
    else if (CheckHitKey(KEY_INPUT_E))                              //Eキーが押されたら
    {
        cameraYaw += cameraRotSpeed * deltaTime;                    //回転角は正の方向
    }
    cameraPos.x = cameraRad * cosf(cameraYaw);                      //カメラのX軸座標
    cameraPos.z = cameraRad * sinf(cameraYaw);                      //カメラのZ軸座標

    SetCameraPositionAndTarget_UpVecY(objPos + cameraPos,
        objPos + VGet(0, 8, 0));                                   //(0,8,0)の視点からプレイヤーを見る角度にカメラ設置
}