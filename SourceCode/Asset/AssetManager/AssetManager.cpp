#include "AssetManager.h"


AssetManager* AssetManager::assetInstance = nullptr;    //AssetManager実態へのポインタ定義

    // @brief AssetManagerコンストラクター //

AssetManager::AssetManager()
{
    SetEnableXAudioFlag(FALSE);
    Set3DSoundOneMetre(20.0f);

}

    // @brief AssetManagerデストラクター //

AssetManager::~AssetManager()
{
    assetInstance->ReleaseAllAsset();       //すべてのアセットを削除
    assetInstance = nullptr;                //ポインタを削除
}

    // @brief AssetManager初期化 //

void AssetManager::Init()
{
    if (!assetInstance)                     //ポインタが空だったら
    {
        assetInstance = new AssetManager;   //ポインタ初期化
    }
}

    // @brief メッシュの取得 //

int AssetManager::GetMesh(std::string meshFileName)
{
    int meshID = 0;
    //---メッシュ登録---//
    auto iter = assetInstance->meshMap.find(meshFileName);   //ファイルが登録されているかどうか検索

    if (iter == assetInstance->meshMap.end())                                               //登録されていなかったら
    {
        meshID = MV1LoadModel(meshFileName.c_str());                                        //新規ファイル読み込み
        if (meshID == -1)                                                                   //IDが空だったら
        {
            return meshID;                                                                  //IDを返す
        }
        assetInstance->meshMap.emplace(meshFileName, meshID);                //ファイルをIDと共に登録
    }

    //---複製したメッシュを返却---//
    meshID = MV1DuplicateModel(assetInstance->meshMap[meshFileName]);             //メッシュ複製、IDに代入
    assetInstance->duplicateMesh.push_back(meshID);                                   //複製を末尾に追加
    return meshID;                                                                         //複製したIDを返す
}

    // @brief アニメーションの取得 //

int AssetManager::GetAnim(std::string animFileName)
{
    int animID = 0;
    //---アニメーション登録---//
    auto iter = assetInstance->animMap.find(animFileName);  //ファイルが登録されているかどうか検索

    if (iter == assetInstance->animMap.end())                                             //登録されていなかったら
    {
        animID = MV1LoadModel(animFileName.c_str());                                      //新規ファイル読み込み
        if (animID == -1)                                                                 //IDが空だったら
        {
            return animID;                                                                //IDを返す
        }
        assetInstance->animMap.emplace(animFileName, animID);               //ファイルをIDと共に登録
    }

    return assetInstance->animMap[animFileName];                                         //アニメーションIDを返す
}

int AssetManager::GetSound(std::string soundFileName)
{
    int meshID = 0;
    //---メッシュ登録---//
    auto iter = assetInstance->soundMap.find(soundFileName);   //ファイルが登録されているかどうか検索

    if (iter == assetInstance->soundMap.end())                                               //登録されていなかったら
    {
        meshID = LoadSoundMem(soundFileName.c_str());                                        //新規ファイル読み込み
        if (meshID == -1)                                                                   //IDが空だったら
        {
            return meshID;                                                                  //IDを返す
        }
        assetInstance->meshMap.emplace(soundFileName, meshID);                //ファイルをIDと共に登録
    }

    //---複製したメッシュを返却---//
    meshID = DuplicateSoundMem(assetInstance->meshMap[soundFileName]);             //メッシュ複製、IDに代入
    assetInstance->duplicateMesh.push_back(meshID);                                   //複製を末尾に追加
    return meshID;                                                                         //複製したIDを返す
}

    // @brief メッシュの削除 //

void AssetManager::ReleaseMesh(int meshID)
{
    auto iter = find(assetInstance->duplicateMesh.begin(),
        assetInstance->duplicateMesh.end(), meshID);                            //複製されたメッシュ内を検索
    if (iter == assetInstance->duplicateMesh.end())                                        //見つからなかったら
    {
        return;                                                                            //結果を返す
    }
    MV1DeleteModel(meshID);                                                         //メッシュ削除

    iter_swap(iter, assetInstance->duplicateMesh.end() - 1);                   //末尾のデータと入れ替える
    assetInstance->duplicateMesh.pop_back();                                                //末尾のデータを削除
}

    // @brief 全アセットの削除 //

void AssetManager::ReleaseAllAsset()
{
    //---アニメーション解放---//
    for (auto& anim : assetInstance->animMap)
    {
        MV1DeleteModel(anim.second);
    }

    //---メッシュ解放---//
    for (auto& mesh : assetInstance->meshMap)
    {
        MV1DeleteModel(mesh.second);
    }

    //サウンド開放
    for (auto& sound : assetInstance->soundMap)
    {
        DeleteSoundMem(sound.second);
    }

    //---複製解放---//
    for (auto dup : assetInstance->duplicateMesh)
    {
        MV1DeleteModel(dup);
    }
    for (auto dup : assetInstance->duplicateSound)
    {
        DeleteSoundMem(dup);
    }


    assetInstance->animMap.clear();             //アニメーションのすべての要素を削除
    assetInstance->meshMap.clear();             //メッシュのすべての要素を削除
    assetInstance->soundMap.clear();
    assetInstance->duplicateMesh.clear();       //複製メッシュのすべての要素を削除
    assetInstance->duplicateSound.clear();
}

    // @brief AssetManagerの解放 //

void AssetManager::Finalize()
{
    ReleaseAllAsset();
    if (assetInstance)                          //ポインタが空じゃなかったら
    {
        delete assetInstance;                   //中身を削除
    }
}