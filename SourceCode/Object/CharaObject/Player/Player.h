#pragma once
#include<DxLib.h>
#include<memory>

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// プレイヤーオブジェクト
/// </summary>
class Player :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Player();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    void OnCollisionEnter(const ObjBase* other) override;

    /// <summary>
    /// 球体の衝突時処理
    /// </summary>
    /// <param name="colmodel">:当たり判定モデル</param>
    void CollHitSphere(int colmodel);

    /// <summary>
    /// 線分の衝突時処理
    /// </summary>
    /// <param name="colmodel">:当たり判定モデル</param>
    void ColHitLine(int colmodel);

private:
    /// <summary>
    /// 移動処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Move(float deltaTime);


    VECTOR UP;                                      //正面
    VECTOR DOWN;                                    //後方
    VECTOR RIGHT;                                   //右
    VECTOR LEFT;                                    //左

    VECTOR inputVec;                                //合成ベクトル
    VECTOR inputVel;                                //速度ベクトル
    float walkStep;                                 //Y軸動作
    bool inputKey;                                  //キー入力判定
    bool canMove;                                   //動作状態

    const float HIT_DISTANCE = 12.0f;               //当たり判定距離
    const VECTOR HIT_AIM_POS = VGet(0, 18, 0);      //判定後視点

    VECTOR camFront;                                //カメラ前方向

    std::unique_ptr<class Sound> plySound;          //サウンド
};