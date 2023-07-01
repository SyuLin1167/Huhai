#pragma once

#include<vector>
#include<unordered_map>

#include"../ObjectBase/ObjectBase.h"
#include"../ObjectBase/ObjectTag.h"

/* ObjManagerクラス */
class ObjManager final
{
public:
    /// <summary>
    /// 初期化処理
    /// </summary>
    static void Init();

    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="newObj">:追加オブジェクト</param>
    static void Entry(ObjBase* newObj);

    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="releaseObj">:削除オブジェクト</param>
    static void Release(ObjBase* releaseObj);

    /// <summary>
    /// 全削除
    /// </summary>
    static void ReleaseAllObj();

    /// <summary>
    /// 全更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    static void Update(float deltaTime);

    /// <summary>
    /// 全描画処理
    /// </summary>
    static void Draw();

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    static void Collision();

    /// <summary>
    /// タグの先頭オブジェクト取得
    /// </summary>
    /// <param name="tag">:タグ</param>
    /// <returns>オブジェクト</returns>
    static ObjBase* GetFirstObj(ObjectTag tag);

    /// <summary>
    /// タグの指定オブジェクト取得
    /// </summary>
    /// <param name="tag">:タグ</param>
    /// <param name="tagNum">:オブジェクト番号</param>
    /// <returns>:オブジェクト</returns>
    static ObjBase* GetObj(ObjectTag tag, int tagNum);

    /// <summary>
    /// 後処理
    /// </summary>
    static void Finalize();

private:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    ObjManager();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ObjManager();

    /// <summary>
    /// 死亡処理
    /// </summary>
    static void Dead();

    static ObjManager* objManager;                                  //自身の実態
    std::vector<ObjBase*>holdObj;                                   //一時保存オブジェクト
    std::unordered_map<ObjectTag, std::vector<ObjBase*>>Object;     //Object[タグ種類][オブジェクト個数]

    class Bloom* bloom;                                             //ブルーム
};