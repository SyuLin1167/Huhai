#pragma once

#include"../../ObjectBase/ObjectBase.h"

/*Manクラス*/
class Man :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Man();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Man();

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
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// 回転処理
    /// </summary>
    void Rotate();

    //アニメーションタイプ
    enum Anim
    {
        CRYING = 0,			//泣き
        DEAD,               //死亡
    };

private:
    bool rotateNow;                 //回転状態
    VECTOR aimDir;                  //目標方向

    class Animation* manAnim;       //アニメーション
    int animType;                   //アニメーションタイプ

    bool isSpeak;                   //会話状態

    class Sound* manSound;          //サウンド
};
