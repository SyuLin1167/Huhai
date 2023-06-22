#pragma once

#include"Base/GhostBase.h"


/* Ghostクラス */
class Ghost :public GhostBase
{
public:
    /// <summary>
    /// Ghostのコンストラクター
    /// </summary>
    Ghost();

    /// <summary>
    /// Ghostのデストラクター
    /// </summary>
    ~Ghost();

    /// <summary>
    /// Ghost更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Ghost描画処理
    /// </summary>
    void Draw()override;


    /// <summary>
    /// Ghost衝突時処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    void OnCollisionEnter(const ObjBase* other)override;

    /// <summary>
    /// Ghost回転処理
    /// </summary>
    void Rotate();

private:
    float moveCount;        //カウント
    bool isFirstMove;       //初動状態
    bool isMove;            //移動状態

    VECTOR aimDir;          //目標方向
    bool rotateNow;         //回転状態

    VECTOR aimPos;          //目標座標
    VECTOR holdPos;         //一時保存座標

    int lightHandle;        //ライトハンドル
};

