#pragma once
#include<DxLib.h>

#include"../../ObjectBase/ObjectBase.h"

/*Doorクラス*/
class Door :public ObjBase
{
public:
    //アニメーションタイプ
    enum AnimType
    {
        IDLE = 0,       //待機
        OPEN,           //開
        CLOSE           //閉
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="scene">:シーン名</param>
    /// <param name="num">:オブジェクト番号</param>
    Door(std::string scene, std::string num = "0");

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Door();

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

private:
    class Animation* doorAnim;			//アニメーション
    int animType;						//アニメーションタイプ

    bool rotateNow;                     //回転状態
    VECTOR aimDir;                      //目標方向

    class Sound* doorSound;             //サウンド

    class ObjBase* player;              //プレイヤーオブジェクト
    class Action* action;               //アクションボタン
};
