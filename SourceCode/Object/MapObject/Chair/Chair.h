#pragma once
#include<memory>

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// 椅子オブジェクト
/// </summary>
class Chair :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Chair();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Chair();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

    //アニメーションタイプ
    enum Anim
    {
        IDLE = 0,           //待機
        MOVE,               //動く
    };

private:
    std::unique_ptr<class Animation> chairAnim;         //アニメーション
    int animType;                       //アニメーション状態

    std::unique_ptr<class Sound> chairSound;            //サウンド
};

