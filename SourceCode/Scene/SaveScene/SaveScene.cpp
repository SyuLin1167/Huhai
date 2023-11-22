#include "SaveScene.h"

#include"../RoomScene/RoomScene.h"

std::unique_ptr<SaveScene> SaveScene::singleton = nullptr;

SaveScene::SaveScene()
    :scene(nullptr)
{
    //処理なし
}

SaveScene::~SaveScene()
{
    //処理なし
}

void SaveScene::CreateInstance()
{
    //インスタンス生成
    if (!singleton.get())
    {
        singleton.reset(new SaveScene);
    }
}

void SaveScene::Save(SceneBase* nowScene)
{
    //シーンをセーブ
    if (singleton->scene.get() != nowScene)
    {
        singleton->scene.reset(nowScene);
    }
}

SceneBase* SaveScene::Load()
{
    //セーブシーンがなかったら初めのRoomSceneを返す
    if (!singleton->scene.get())
    {
        return new RoomScene;
    }

    return singleton->scene.get();
}