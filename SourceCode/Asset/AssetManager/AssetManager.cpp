#include "AssetManager.h"

std::unique_ptr<AssetManager> AssetManager::singleton = nullptr;

AssetManager::AssetManager()
{
    SetEnableXAudioFlag(TRUE);
    Set3DSoundOneMetre(10.0f);
}

AssetManager::~AssetManager()
{
    //全アセット削除
    ReleaseAllAsset();
}

void AssetManager::Init()
{
    //インスタンス生成
    if (!singleton)
    {
        singleton.reset(new AssetManager);
    }
}

int AssetManager::GetGraph(std::string fileName)
{
    int meshID = 0;

    //ファイルを検索して登録されていなかったら登録
    auto findFile = singleton->graphMap.find(fileName);
    if (findFile == singleton->graphMap.end())
    {
        meshID = LoadGraph(fileName.c_str());

        //IDが空ならそのまま返す
        if (meshID == -1)
        {
            return meshID;
        }

        singleton->graphMap.emplace(fileName, meshID);
    }

    //グラフIDを返す
    return singleton->graphMap[fileName];
}

int AssetManager::GetMesh(std::string fileName)
{
    int meshID = 0;

    //ファイルを検索して登録されていなかったら登録
    auto iter = singleton->meshMap.find(fileName);
    if (iter == singleton->meshMap.end())
    {
        meshID = MV1LoadModel(fileName.c_str());

        //IDが空ならそのまま返す
        if (meshID == -1)
        {
            return meshID;
        }

        singleton->meshMap.emplace(fileName, meshID);
    }

    //複製したメッシュIDを返す
    meshID = MV1DuplicateModel(singleton->meshMap[fileName]);
    singleton->dupMesh.push_back(meshID);
    return meshID;
}

int AssetManager::GetAnim(std::string fileName)
{
    int animID = 0;

    //ファイルを検索して登録されていなかったら登録
    auto iter = singleton->animMap.find(fileName);
    if (iter == singleton->animMap.end())
    {
        animID = MV1LoadModel(fileName.c_str());

        //IDが空ならそのまま返す
        if (animID == -1)
        {
            return animID;
        }

        singleton->animMap.emplace(fileName, animID);
    }

    //アニメーションIDを返す
    return singleton->animMap[fileName];
}

int AssetManager::GetSound(std::string fileName)
{
    int meshID = 0;

    //ファイルを検索して登録されていなかったら登録
    auto iter = singleton->soundMap.find(fileName);

    if (iter == singleton->soundMap.end())
    {
        meshID = LoadSoundMem(fileName.c_str());

        //IDが空ならそのまま返す
        if (meshID == -1)
        {
            return meshID;
        }

        singleton->meshMap.emplace(fileName, meshID);
    }

    //複製したサウンドIDを返す
    meshID = DuplicateSoundMem(singleton->meshMap[fileName]);
    singleton->dupMesh.push_back(meshID);
    return meshID;
}

void AssetManager::ReleaseMesh(int meshID)
{
    //複製したメッシュ内検索
    auto iter = find(singleton->dupMesh.begin(),
        singleton->dupMesh.end(), meshID);

    //見つからなかったら結果を返す
    if (iter == singleton->dupMesh.end())
    {
        return;
    }

    //見つかったら末尾移動して削除
    MV1DeleteModel(meshID);
    std::iter_swap(iter, singleton->dupMesh.end() - 1);
    singleton->dupMesh.pop_back();
}

void AssetManager::ReleaseAllAsset()
{
    //グラフ解放
    for (auto& graph : singleton->graphMap)
    {
        DeleteGraph(graph.second);
    }
    //アニメーション解放
    for (auto& anim : singleton->animMap)
    {
        MV1DeleteModel(anim.second);
    }

    //メッシュ解放
    for (auto& mesh : singleton->meshMap)
    {
        MV1DeleteModel(mesh.second);
    }

    //サウンド解放
    for (auto& sound : singleton->soundMap)
    {
        DeleteSoundMem(sound.second);
    }

    //複製解放-
    for (auto dup : singleton->dupMesh)
    {
        MV1DeleteModel(dup);
    }
    for (auto dup : singleton->dupSound)
    {
        DeleteSoundMem(dup);
    }

    //アセットの要素削除
    singleton->graphMap.clear();
    singleton->animMap.clear();
    singleton->meshMap.clear();
    singleton->soundMap.clear();

    //複製の要素削除
    singleton->dupMesh.clear();
    singleton->dupSound.clear();
}