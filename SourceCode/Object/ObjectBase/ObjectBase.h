#pragma once
#include<DxLib.h>

#include"ObjectTag.h"
#include"../../Math/Math.h"
#include"../../Collision/Collision.h"
#include"../../Collision/CollisionType.h"

constexpr auto SCREEN_WIDTH = 1920;       //スクリーン幅指定
constexpr auto SCREEN_HEIGHT = 1080;      //スクリーン高さ指定
//---スクリーンサイズの例: 640*480, 800*600, 1024*768, 1280*1024, 1280*720, 1920*1080---//

/*親クラス*/
class ObjectBase
{
public:
    /// <summary>
    /// コンストラクタ―
    /// </summary>
    /// <param name="tag">:タグ</param>
    ObjectBase(ObjectTag tag);

    /// <summary>
    /// コンストラクタ―(位置・方向セット)
    /// </summary>
    /// <param name="tag">:タグ</param>
    /// <param name="pos">:座標</param>
    /// <param name="angle">:方向</param>
    ObjectBase(ObjectTag tag, VECTOR pos, VECTOR angle = { 0,0,0 });
    
    /// <summary>
    /// デストラクター
    /// </summary>
    virtual ~ObjectBase();

    /// <summary>
    /// 座標取得
    /// </summary>
    /// <returns>セットされた座標</returns>
    const VECTOR& GetPos()const { return objPos; }

    /// <summary>
    /// 座標設定
    /// </summary>
    /// <param name="setPos">:座標にセットする値</param>
    void SetPos(const VECTOR setPos) { objPos = setPos; }

    /// <summary>
    /// 方向取得
    /// </summary>
    /// <returns>セットされた向き</returns>
    const VECTOR& GetDir()const { return objDir; }

    /// <summary>
    /// 方向設定
    /// </summary>
    /// <param name="dir">:向きにセットする値</param>
    void SetDir(const VECTOR dir) { objDir = dir; }

    /// <summary>
    /// 可視化判定
    /// </summary>
    /// <returns>可視化状態</returns>
    bool IsVisible() { return isVisible; }

    /// <summary>
    /// 可視化設定
    /// </summary>
    /// <param name="visible">見えるかどうか</param>
    void SetVisible(bool visible) { isVisible = visible; }

    /// <summary>
    /// 生死判定
    /// </summary>
    /// <returns>生死状態</returns>
    bool IsAlive() { return isAlive; }

    /// <summary>
    /// 生死設定
    /// </summary>
    /// <param name="alive">:生きているかどうか</param>
    void SetAlive(bool alive) { isAlive = alive; }


    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    virtual void Update(float deltaTime) = 0;

    /// <summary>
    /// 描画処理
    /// </summary>
    virtual void Draw();

    /// <summary>
    /// オブジェクトのタグ取得
    /// </summary>
    /// <returns>タグ種類</returns>
    ObjectTag GetTag()const { return objTag; }

    //---当たり判定関連---//

    /// <summary>
    /// 衝突時処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    virtual void OnCollisionEnter(const ObjectBase*other){}

    /// <summary>
    /// オブジェクトとの当たり判定
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    virtual void ColWithOther(ObjectBase* other) {};

    /// <summary>
    /// オブジェクトの当たり判定種
    /// </summary>
    /// <returns>当たり判定種</returns>
    CollisionType GetColType()const { return colType; }

    /// <summary>
    /// 線分当たり判定
    /// </summary>
    /// <returns>当たり判定Line</returns>
    Line GetColLine()const { return colLine; }

    /// <summary>
    /// 球当たり判定
    /// </summary>
    /// <returns>当たり判定Sphere</returns>
    Sphere GetColSphere()const { return colSphere; }

    /// <summary>
    /// カプセル当たり判定
    /// </summary>
    /// <returns>当たり判定Capsule</returns>
    Capsule GetColCapsule()const { return colCapsule; }

    /// <summary>
    /// モデル当たり判定
    /// </summary>
    /// <returns>当たり判定Model</returns>
    int GetColModel()const { return colModel; }

protected:
    /// <summary>
    /// Collision更新処理
    /// </summary>
    void ColUpdate();

    /// <summary>
    /// Collision描画処理
    /// </summary>
    void ColDraw();

    ObjectTag objTag;                           //オブジェクトの種類
    int objHandle;                              //モデルハンドル
    VECTOR objPos;                              //ワールド座標
    VECTOR objDir;                              //ワールド方向
    VECTOR objScale;                            //オブジェクトの大きさ

    float objSpeed;                             //オブジェクトの速度

    bool isVisible;                             //可視化状態
    bool isAlive;                               //生死状態

    //---当たり判定関連---//
    CollisionType colType;                      //当たり判定種
    Line colLine;                    //当たり判定Line
    Sphere colSphere;                //当たり判定Sphere
    Capsule colCapsule;              //当たり判定Capsule
    int colModel;                               //当たり判定Model
};

