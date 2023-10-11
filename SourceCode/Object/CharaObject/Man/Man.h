#pragma once
#include<memory>

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// Manクラス
/// </summary>
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
    /// アニメーションタイプ
    /// </summary>
    enum Anim
    {
        CRYING = 0,         //泣き
        DEAD,               //死亡
    };

private:
    const float ROTATE_VELOCITY = 5.0f;             //回転速度
    bool isSpeak;                                   //会話状態

    std::unique_ptr<class Animation> manAnim;       //アニメーション
    int animType;                                   //アニメーションタイプ

    std::unique_ptr<class Sound> manSound;          //サウンド
};
