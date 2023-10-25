#pragma once
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<memory>

#include"../ObjectBase/ObjBase.h"
#include"../ObjectBase/ObjTag.h"

/// <summary>
/// オブジェクトの管理
/// </summary>
class ObjManager final
{
public:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ObjManager();

    /// <summary>
    /// 初期化処理
    /// </summary>
    static void Init();

    /// <summary>
    /// オブジェクト追加処理
    /// </summary>
    /// <param name="newObj">:追加オブジェクト</param>
    static void AddObj(ObjBase* newObj);

    /// <summary>
    /// 全オブジェクト更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    static void UpdateAllObj(const float deltaTime);

    /// <summary>
    /// 全オブジェクト当たり判定処理
    /// </summary>
    static void OnCollision();

    /// <summary>
    /// 全オブジェクト描画処理
    /// </summary>
    static void DrawAllObj();

    /// <summary>
    /// オブジェクト削除処理
    /// </summary>
    /// <param name="releaseObj">:削除オブジェクト</param>
    static void DeleteObj(std::shared_ptr<ObjBase>& releaseObj);

    /// <summary>
    /// 全オブジェクト削除処理
    /// </summary>
    static void DeleteAllObj();

    /// <summary>
    /// タグの先頭オブジェクト取得
    /// </summary>
    /// <param name="tag">:タグ</param>
    /// <returns>オブジェクト</returns>
    static ObjBase* GetFirstObj(ObjTag tag);

    /// <summary>
    /// タグの指定オブジェクト取得
    /// </summary>
    /// <param name="tag">:タグ</param>
    /// <param name="tagNum">:オブジェクト番号</param>
    /// <returns>:オブジェクト</returns>
    static ObjBase* GetObj(ObjTag tag, int tagNum);

private:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    ObjManager();

    /// <summary>
    /// オブジェクト死亡処理
    /// </summary>
    static void OnDeadObj();

    static std::unique_ptr<ObjManager> singleton;       //自身の実態
    //std::vector<ObjBase*>holdObj;                     //一時保存オブジェクト
    std::unordered_map<ObjTag, std::vector<
        std::shared_ptr<ObjBase>>> object;              //オブジェクト

    std::unique_ptr<class Bloom> bloom;                 //ブルーム
};