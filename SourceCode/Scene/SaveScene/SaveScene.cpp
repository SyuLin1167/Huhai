#include "SaveScene.h"

#include"../RoomScene/RoomScene.h"

//���Ԃւ̃|�C���^��`
std::unique_ptr<SaveScene> SaveScene::saveScene = nullptr;

/// <summary>
/// �R���X�g���N�^(�V���O���g��)
/// </summary>
SaveScene::SaveScene()
    :scene(nullptr)
{
    //�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SaveScene::~SaveScene()
{
    //�����Ȃ�
}

/// <summary>
/// �C���X�^���X��������
/// </summary>
void SaveScene::CreateInstance()
{
    //�C���X�^���X����
    if (!saveScene.get())
    {
        saveScene.reset(new SaveScene);
    }
}

/// <summary>
/// �Z�[�u����
/// </summary>
/// <param name="nowScene">:�ۑ�����V�[��</param>
void SaveScene::Save(SceneBase* nowScene)
{
    //�V�[�����Z�[�u
    if (saveScene->scene.get() != nowScene)
    {
        saveScene->scene.reset(nowScene);
    }
}

/// <summary>
/// ���[�h����
/// </summary>
/// <returns>:�Z�[�u�V�[��</returns>
SceneBase* SaveScene::Load()
{
    //�Z�[�u�V�[�����Ȃ������珉�߂�RoomScene��Ԃ�
    if (!saveScene->scene.get())
    {
        return new RoomScene;
    }

    return saveScene->scene.get();
}