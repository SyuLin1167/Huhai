#pragma once
#include<DxLib.h>

#include"../../ObjectBase/ObjectBase.h"

/*Doorクラス*/
class Door :public ObjBase
{
    ObjBase* player;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Door();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">:ワールド座標</param>
    /// <param name="dir">:方向</param>
    Door(VECTOR pos, VECTOR dir);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Door();

    /// <summary>
    /// 読み込み処理
    /// </summary>
    void Load();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// アニメーション処理
    /// </summary>
    /// <param name="animtype">:アニメーションタイプ</param>
    void MoveAnim(int animtype);

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    //アニメーションタイプ
    enum Anim
    {
        IDLE = 0,       //待機
        OPEN,           //開
        CLOSE           //閉
    };

private:
    class Animation* doorAnim;			//アニメーション
    int animType;						//アニメーションタイプ

    bool rotateNow;                     //回転状態
    VECTOR aimDir;                      //目標方向

    class Sound* doorSound;             //サウンド
};
