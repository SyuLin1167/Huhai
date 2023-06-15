#pragma once
#include<DxLib.h>
#include<string>
#include<unordered_map>

    /* アセット管理クラス */
class AssetManager final
{
public:
    /// <summary>
    /// AssetManager初期化処理
    /// </summary>
    static void Init();

    /// <summary>
    /// メッシュの取得
    /// </summary>
    /// <param name="fileName">:メッシュファイル名</param>
    /// <returns>複製したメッシュID</returns>
    static int GetMesh(std::string meshFileName);

    /// <summary>
    /// アニメーションの取得
    /// </summary>
    /// <param name="fileName">:アニメーションファイル名</param>
    /// <returns>アニメーションID</returns>
    static int GetAnim(std::string animFileName);

    /// <summary>
    /// サウンドの取得
    /// </summary>
    /// <param name="soundFileName">:サウンドファイル名</param>
    /// <returns>複製したサウンドID</returns>
    static int GetSound(std::string soundFileName);

    /// <summary>
    /// メッシュの削除
    /// </summary>
    /// <param name="meshID">:メッシュID</param>
    static void ReleaseMesh(int meshID);

    /// <summary>
    /// 全アセットの削除
    /// </summary>
    static void ReleaseAllAsset();

    /// <summary>
    /// AssetManagerの解放
    /// </summary>
    static void Finalize();

private:
    /// <summary>
    /// AssetManagerコンストラクター(シングルトン)
    /// </summary>
    AssetManager();

    /// <summary>
    /// AssetManagerデストラクター
    /// </summary>
    ~AssetManager();

    static AssetManager* assetInstance;     //AssetManagerの実態
    std::unordered_map<std::string, int>meshMap;      //メッシュ(オリジナル)
    std::unordered_map<std::string, int>animMap;      //アニメーション(オリジナル)
    std::unordered_map<std::string, int>soundMap;     //サウンド(オリジナル)
    std::vector<int> duplicateMesh;              //メッシュ(複製)
    std::vector<int> duplicateSound;             //サウンド(複製)
};
