#include "Save.h"

#include"../RoomScene/Room.h"

//���Ԃւ̃|�C���^��`
SaveScene* SaveScene::save = nullptr;

// �R���X�g���N�^ //

SaveScene::SaveScene()
    :saveScene(nullptr)
{
}

// �f�X�g���N�^ //

SaveScene::~SaveScene()
{
}

// ���������� //

void SaveScene::Init()
{
    //�C���X�^���X����
    if (!save)
    {
        save = new SaveScene;
    }
}

// �㏈�� //


void SaveScene::Finalize()
{
    //�C���X�^���X�폜 
    if (save->saveScene)
    {
        delete save->saveScene;
    }
    if (save)
    {
        delete save;
    }
}

// �Z�[�u���� //

void SaveScene::Save(SceneBase* scene)
{
    //�V�[�����Z�[�u
    if (save->saveScene != scene)
    {
        save->saveScene = scene;
    }
}

// ���[�h���� //

SceneBase* SaveScene::Load()
{
    //�Z�[�u�V�[�����Ȃ������珉�߂�RoomScene��Ԃ�
    if (!save->saveScene)
    {
        return new RoomScene;
    }

    return save->saveScene;
}