#pragma once

#include"Base/GhostBase.h"


/// <summary>
/// Ghostクラス
/// </summary>
class Ghost :public GhostBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Ghost();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Ghost();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;


    /// <summary>
    /// 当たり判定処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    void OnCollisionEnter(const ObjBase* other) override;
private:
    const float GHOST_MOVE_POS_Y = 1.2f;                                //移動時のY座標

    float moveCount;                                                    //カウント
    bool isFirstMove;                                                   //初動状態

    VECTOR aimPos;                                                      //目標座標
    VECTOR holdPos;                                                     //一時保存座標

    const float HIT_DISTANCE = 12.0f;                                   //当たり判定距離

    int lightHandle;                                                    //ライトハンドル
    const VECTOR LIGHT_POS = VGet(0.0f, 10.0f, 0.0f);                   //ライト座標
    const float LIGHT_RANGE = 50.0f;                                    //距離減衰有効距離
    const float LIGHT_ATTEN2 = 0.005f;                                  //距離減衰係数
    const COLOR_F LIGHT_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);      //ライトの色
};

