#include "SaveScene.h"

#include"../RoomScene/RoomScene.h"

//実態へのポインタ定義
std::unique_ptr<SaveScene> SaveScene::saveScene = nullptr;

// コンストラクタ //

SaveScene::SaveScene()
    :scene(nullptr)
{
}

// デストラクタ //

SaveScene::~SaveScene()
{
}

// インスタンス生成処理 //

void SaveScene::CreateInstance()
{
    //インスタンス生成
    if (!saveScene.get())
    {
        saveScene.reset(new SaveScene);
    }
}

// 後処理 //


void SaveScene::Finalize()
{
}

// セーブ処理 //

void SaveScene::Save(SceneBase* nowScene)
{
    //シーンをセーブ
    if (saveScene->scene.get() != nowScene)
    {
        saveScene->scene.reset(nowScene);
    }
}

// ロード処理 //

SceneBase* SaveScene::Load()
{
    //セーブシーンがなかったら初めのRoomSceneを返す
    if (!saveScene->scene.get())
    {
        return new RoomScene;
    }

    return saveScene->scene.get();
}