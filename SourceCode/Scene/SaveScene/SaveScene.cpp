#include "SaveScene.h"

#include"../RoomScene/RoomScene.h"

std::unique_ptr<SaveScene> SaveScene::singleton = nullptr;

SaveScene::SaveScene()
    :scene(nullptr)
{
    //�����Ȃ�
}

SaveScene::~SaveScene()
{
    //�����Ȃ�
}

void SaveScene::CreateInstance()
{
    //�C���X�^���X����
    if (!singleton.get())
    {
        singleton.reset(new SaveScene);
    }
}

void SaveScene::Save(SceneBase* nowScene)
{
    //�V�[�����Z�[�u
    if (singleton->scene.get() != nowScene)
    {
        singleton->scene.reset(nowScene);
    }
}

SceneBase* SaveScene::Load()
{
    //�Z�[�u�V�[�����Ȃ������珉�߂�RoomScene��Ԃ�
    if (!singleton->scene.get())
    {
        return new RoomScene;
    }

    return singleton->scene.get();
}