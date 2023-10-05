#pragma once
#include<DxLib.h>
#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<string.h>
#include<string>
#include<fstream>

#include"ObjectTag.h"
#include"../../Math/Math.h"
#include"../../Collision/Collision.h"
#include"../../Collision/CollisionType.h"

/*ObjBaseクラス*/
class ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="tag">:タグ</param>
    ObjBase(ObjectTag tag);


    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ObjBase();

    /// <summary>
    /// jsonファイル読み込み処理
    /// </summary>
    /// <param name="fileName"></param>
    void LoadJsonFile(std::string fileName);

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
    bool IsVisible()const { return isVisible; }

    /// <summary>
    /// 可視化設定
    /// </summary>
    /// <param name="visible">見えるかどうか</param>
    void SetVisible(const bool visible) { isVisible = visible; }

    /// <summary>
    /// 生死判定
    /// </summary>
    /// <returns>生死状態</returns>
    bool IsAlive()const { return isAlive; }

    /// <summary>
    /// 生死設定
    /// </summary>
    /// <param name="alive">:生きているかどうか</param>
    void SetAlive(const bool alive) { isAlive = alive; }


    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    virtual void Update(float deltaTime) = 0;

    /// <summary>
    /// 描画処理
    /// </summary>
    virtual void Draw() = 0;

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
    virtual void OnCollisionEnter(const ObjBase* other) {}

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    virtual void ColWithOther(ObjBase* other) {};

    /// <summary>
    /// 当たり判定種
    /// </summary>
    /// <returns>当たり判定種</returns>
    CollisionType GetColType()const { return colType; }

    /// <summary>
    /// 線分当たり判定
    /// </summary>
    /// <returns>当たり判定Line</returns>
    Line GetColLine()const { return colLine; }

    /// <summary>
    /// 球体当たり判定
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

    rapidjson::Document doc;                    //ドキュメント

    ObjectTag objTag;                           //オブジェクトタグ
    int objHandle;                              //オブジェクトハンドル
    VECTOR objPos;                              //ワールド座標
    VECTOR objDir;                              //ワールド方向
    VECTOR objScale;                            //オブジェクトサイズ

    float objSpeed;                             //移動速度

    bool isVisible;                             //可視化状態
    bool isAlive;                               //生死状態

    //---当たり判定関連---//
    CollisionType colType;                      //当たり判定種
    Line colLine;                               //線分
    Sphere colSphere;                           //球体
    Capsule colCapsule;                         //カプセル
    int colModel;                               //モデル
};

