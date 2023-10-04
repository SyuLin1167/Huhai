#include "SaveScene.h"

#include"../RoomScene/RoomScene.h"

//���Ԃւ̃|�C���^��`
std::unique_ptr<SaveScene> SaveScene::saveScene = nullptr;

// �R���X�g���N�^ //

SaveScene::SaveScene()
    :scene(nullptr)
{
}

// �f�X�g���N�^ //

SaveScene::~SaveScene()
{
}

// �C���X�^���X�������� //

void SaveScene::CreateInstance()
{
    //�C���X�^���X����
    if (!saveScene.get())
    {
        saveScene.reset(new SaveScene);
    }
}

// �㏈�� //


void SaveScene::Finalize()
{
}

// �Z�[�u���� //

void SaveScene::Save(SceneBase* nowScene)
{
    //�V�[�����Z�[�u
    if (saveScene->scene.get() != nowScene)
    {
        saveScene->scene.reset(nowScene);
    }
}

// ���[�h���� //

SceneBase* SaveScene::Load()
{
    //�Z�[�u�V�[�����Ȃ������珉�߂�RoomScene��Ԃ�
    if (!saveScene->scene.get())
    {
        return new RoomScene;
    }

    return saveScene->scene.get();
}