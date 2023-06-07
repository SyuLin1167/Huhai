#pragma once
#include<DxLib.h>
#include<string>
#include<unordered_map>

using namespace std;

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
    static int GetMesh(string meshFileName);

    /// <summary>
    /// アニメーションの取得
    /// </summary>
    /// <param name="fileName">:アニメーションファイル名</param>
    /// <returns>アニメーションID</returns>
    static int GetAnim(string animFileName);

    /// <summary>
    /// サウンドの取得
    /// </summary>
    /// <param name="soundFileName">:サウンドファイル名</param>
    /// <returns>複製したサウンドID</returns>
    static int GetSound(string soundFileName);

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
    unordered_map<string, int>meshMap;      //メッシュ(オリジナル)
    unordered_map<string, int>animMap;      //アニメーション(オリジナル)
    unordered_map<string, int>soundMap;     //サウンド(オリジナル)
    vector<int> duplicateMesh;              //メッシュ(複製)
    vector<int> duplicateSound;             //サウンド(複製)
};

