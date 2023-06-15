#pragma once
#include<DxLib.h>

#include"../../ObjectManager/ObjManager.h"
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Collision/Collision.h"
#include"../../../Asset/Sound/Sound.h"

        /* Playerのクラス */
class Player :public ObjectBase
{
public:
    /// <summary>
    /// Playerコンストラクター
    /// </summary>
    Player();

    /// <summary>
    /// Playerデストラクター
    /// </summary>
    ~Player();

    /// <summary>
    /// Player更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// Player描画処理
    /// </summary>
    void Draw() override;

    /// <summary>
    /// Player衝突時処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    void OnCollisionEnter(const ObjectBase* other)override;

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

    void Rotate();

private:
    /// <summary>
    /// Player移動処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Move(float deltaTime);

    bool canMove;

    //正面
    VECTOR UP;
    //後方
    VECTOR DOWN;
    //右
    VECTOR RIGHT;
    //左
    VECTOR LEFT;

    VECTOR inputVec;						//合成ベクトル
    VECTOR inputVel;						//速度ベクトル
    bool inputKey;							//キー入力判定
    bool rotateNow;							//現在回転中かどうか
    VECTOR aimDir;

    //---当たり判定関連---//
    Sphere colSphere;			//当たり判定球

    //---カメラ関連---//
    VECTOR camFront;						//カメラ前方向

    class Sound* plySound;
};