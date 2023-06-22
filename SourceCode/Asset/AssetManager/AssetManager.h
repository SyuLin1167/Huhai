#pragma once
#include<DxLib.h>
#include<string>
#include<unordered_map>

/* AssetManagerクラス */
class AssetManager final
{
public:
    /// <summary>
    /// 初期化処理
    /// </summary>
    static void Init();

    /// <summary>
    /// メッシュ取得
    /// </summary>
    /// <param name="fileName">:ファイル名</param>
    /// <returns>複製したメッシュID</returns>
    static int GetMesh(std::string fileName);

    /// <summary>
    /// アニメーション取得
    /// </summary>
    /// <param name="fileName">:ファイル名</param>
    /// <returns>アニメーションID</returns>
    static int GetAnim(std::string fileName);

    /// <summary>
    /// サウンド取得
    /// </summary>
    /// <param name="fileName">:ファイル名</param>
    /// <returns>複製したサウンドID</returns>
    static int GetSound(std::string fileName);

    /// <summary>
    /// メッシュ削除
    /// </summary>
    /// <param name="meshID">:メッシュID</param>
    static void ReleaseMesh(int meshID);

    /// <summary>
    /// 全アセット削除
    /// </summary>
    static void ReleaseAllAsset();

    /// <summary>
    /// 後処理
    /// </summary>
    static void Finalize();

private:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    AssetManager();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~AssetManager();

    static AssetManager* assetMgr;                      //自身の実態
    std::unordered_map<std::string, int>meshMap;        //メッシュ(オリジナル)
    std::unordered_map<std::string, int>animMap;        //アニメーション(オリジナル)
    std::unordered_map<std::string, int>soundMap;       //サウンド(オリジナル)
    std::vector<int> dupMesh;                     //メッシュ(複製)
    std::vector<int> dupSound;                    //サウンド(複製)
};
