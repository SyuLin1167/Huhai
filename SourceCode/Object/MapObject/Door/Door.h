#pragma once
#include<DxLib.h>

#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/Model/Model.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Collision/Collision.h"

        /*Doorクラス*/
class Door :public ObjectBase
{
    ObjectBase* player;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Door();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="doorPos">:ドアのワールド座標</param>
    /// <param name="doorAngle">:ドアの方向</param>
    Door(VECTOR doorPos, VECTOR doorAngle);

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

    enum Anim
    {
        IDLE = 0,			//待機
        OPEN,			//開
        CLOSE			//閉
    };
private:
    //---アニメーション関連---//
    class Animation* doorAnim;			//アニメーション
    int animType;						//アニメーション状態

    class Model* doorModel;

    class Sound* doorSound;
};
