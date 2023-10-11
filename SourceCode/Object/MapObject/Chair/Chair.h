#pragma once

#include"../../ObjectBase/ObjBase.h"

/*Chairクラス*/
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

    //アニメーションタイプ
    enum Anim
    {
        IDLE = 0,			//待機
        MOVE,               //動く
    };

private:
    class Animation* ChairAnim;			//アニメーション
    int animType;						//アニメーション状態

    class Sound* chairSound;            //サウンド
};

