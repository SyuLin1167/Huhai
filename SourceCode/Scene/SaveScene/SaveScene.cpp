#include "SaveScene.h"

#include"../RoomScene/RoomScene.h"

//実態へのポインタ定義
std::unique_ptr<SaveScene> SaveScene::saveScene = nullptr;

/// <summary>
/// コンストラクタ(シングルトン)
/// </summary>
SaveScene::SaveScene()
    :scene(nullptr)
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SaveScene::~SaveScene()
{
    //処理なし
}

/// <summary>
/// インスタンス生成処理
/// </summary>
void SaveScene::CreateInstance()
{
    //インスタンス生成
    if (!saveScene.get())
    {
        saveScene.reset(new SaveScene);
    }
}

/// <summary>
/// セーブ処理
/// </summary>
/// <param name="nowScene">:保存するシーン</param>
void SaveScene::Save(SceneBase* nowScene)
{
    //シーンをセーブ
    if (saveScene->scene.get() != nowScene)
    {
        saveScene->scene.reset(nowScene);
    }
}

/// <summary>
/// ロード処理
/// </summary>
/// <returns>:セーブシーン</returns>
SceneBase* SaveScene::Load()
{
    //セーブシーンがなかったら初めのRoomSceneを返す
    if (!saveScene->scene.get())
    {
        return new RoomScene;
    }

    return saveScene->scene.get();
}