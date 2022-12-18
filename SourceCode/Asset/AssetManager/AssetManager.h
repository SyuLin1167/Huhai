#pragma once
#include<DxLib.h>
#include<string>
#include<unordered_map>

using namespace std;

/* アセット管理クラス */
class AssetManager
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
    /// <returns></returns>
    static int GetMesh(string meshFileName);

    /// <summary>
    /// アニメーションの取得
    /// </summary>
    /// <param name="fileName">:アニメーションファイル名</param>
    /// <returns></returns>
    static int GetAnim(string animFileName);

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
    vector<int> duplicateMesh;              //メッシュ(コピー)
};

