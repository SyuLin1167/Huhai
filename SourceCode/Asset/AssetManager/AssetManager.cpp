#include "AssetManager.h"

//実態へのポインタ定義
AssetManager* AssetManager::assetMgr = nullptr;

// コンストラクタ //

AssetManager::AssetManager()
{
    SetEnableXAudioFlag(FALSE);
    Set3DSoundOneMetre(20.0f);
}

// デストラクタ //

AssetManager::~AssetManager()
{
}

// 初期化処理 //

void AssetManager::Init()
{
    //インスタンス生成
    if (!assetMgr)
    {
        assetMgr = new AssetManager;
    }
}

// メッシュ取得 //

int AssetManager::GetMesh(std::string fileName)
{
    int meshID = 0;
    //ファイルを検索して登録されていなかったら登録
    auto iter = assetMgr->meshMap.find(fileName);
    if (iter == assetMgr->meshMap.end())
    {
        meshID = MV1LoadModel(fileName.c_str());
        
        //IDが空ならそのまま返す
        if (meshID == -1)
        {
            return meshID;
        }

        assetMgr->meshMap.emplace(fileName, meshID);
    }

    //複製したメッシュIDを返す
    meshID = MV1DuplicateModel(assetMgr->meshMap[fileName]);
    assetMgr->dupMesh.push_back(meshID);
    return meshID;
}

// アニメーション取得 //

int AssetManager::GetAnim(std::string fileName)
{
    int animID = 0;
    //ファイルを検索して登録されていなかったら登録
    auto iter = assetMgr->animMap.find(fileName);
    if (iter == assetMgr->animMap.end())
    {
        animID = MV1LoadModel(fileName.c_str());

        //IDが空ならそのまま返す
        if (animID == -1)
        {
            return animID;
        }

        assetMgr->animMap.emplace(fileName, animID);
    }

    //アニメーションIDを返す
    return assetMgr->animMap[fileName];
}

// サウンド取得 //

int AssetManager::GetSound(std::string fileName)
{
    int meshID = 0;
    //ファイルを検索して登録されていなかったら登録
    auto iter = assetMgr->soundMap.find(fileName);

    if (iter == assetMgr->soundMap.end())
    {
        meshID = LoadSoundMem(fileName.c_str());

        //IDが空ならそのまま返す
        if (meshID == -1)
        {
            return meshID;
        }

        assetMgr->meshMap.emplace(fileName, meshID);
    }

    //複製したサウンドIDを返す
    meshID = DuplicateSoundMem(assetMgr->meshMap[fileName]);
    assetMgr->dupMesh.push_back(meshID);
    return meshID;
}

    // @brief メッシュの削除 //

void AssetManager::ReleaseMesh(int meshID)
{
    //複製したメッシュ内検索
    auto iter =find(assetMgr->dupMesh.begin(),
        assetMgr->dupMesh.end(), meshID);

    //見つからなかったら結果を返す
    if (iter == assetMgr->dupMesh.end())
    {
        return;
    }

    //見つかったら末尾移動して削除
    MV1DeleteModel(meshID);
    iter_swap(iter, assetMgr->dupMesh.end() - 1);
    assetMgr->dupMesh.pop_back();
}

// 全アセット削除 //

void AssetManager::ReleaseAllAsset()
{
    //アニメーション解放
    for (auto& anim : assetMgr->animMap)
    {
        MV1DeleteModel(anim.second);
    }

    //メッシュ解放
    for (auto& mesh : assetMgr->meshMap)
    {
        MV1DeleteModel(mesh.second);
    }

    //サウンド解放
    for (auto& sound : assetMgr->soundMap)
    {
        DeleteSoundMem(sound.second);
    }

    //---複製解放---//
    for (auto dup : assetMgr->dupMesh)
    {
        MV1DeleteModel(dup);
    }
    for (auto dup : assetMgr->dupSound)
    {
        DeleteSoundMem(dup);
    }

    //アセットの要素削除
    assetMgr->animMap.clear();
    assetMgr->meshMap.clear();
    assetMgr->soundMap.clear();

    //複製の要素削除
    assetMgr->dupMesh.clear();
    assetMgr->dupSound.clear();
}

// 後処理 //

void AssetManager::Finalize()
{
    //全アセット削除
    ReleaseAllAsset();

    //インスタンス削除
    if (assetMgr)
    {
        delete assetMgr;
    }
}