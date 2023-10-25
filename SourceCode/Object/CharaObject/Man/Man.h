#pragma once
#include<memory>

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// 男性オブジェクト
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
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

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
