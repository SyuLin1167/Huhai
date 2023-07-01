#include "SceneManager.h"

#include"../../GameSetting/GameSetting.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"
#include "../TitleScene/Title.h"
#include"../../UI/PauseMenu/Pause.h"
#include "../Save/Save.h"


// �R���X�g���N�^ //

SceneManager::SceneManager()
    :gameSetting(nullptr)
    , timeMgr(nullptr)
    , tmpScene(nullptr)
{
    //�C���X�^���X����
    gameSetting = new GameSetting;
    timeMgr = new TimeManager;
}

// �f�X�g���N�^ //

SceneManager::~SceneManager()
{
    //�C���X�^���X�̌㏈��
    if (gameSetting)
    {
        delete gameSetting;
    }
    if (timeMgr)
    {
        delete timeMgr;
    }
}

// ���������� //

int SceneManager::Init()
{
    //�Q�[���̃Z�b�e�B���O
    if (gameSetting->Init() == -1)
    {
        return -1;
    }

    //�Ǘ��N���X�̏�����
    ObjManager::Init();
    AssetManager::Init();

    SaveScene::Init();

    //�����V�[���ݒ�
    nowScene.push(new TitleScene);

    return 0;
}

// �㏈�� //

void SceneManager::Finalize()
{
    //�Ǘ��N���X�̌㏈��
    ObjManager::Finalize();
    AssetManager::Finalize();

    while(!nowScene.empty())
    {
        nowScene.pop();
    }

    //�Z�b�e�B���O�̌㏈��
    gameSetting->Finalize();
}

// �X�V���� //

void SceneManager::Update()
{
    //�V�[���̍X�V����
    timeMgr->Update();

    //tmpScene�Ɍ��݂̃V�[������
    tmpScene = nowScene.top()->Update(timeMgr->DeltaTime());
}

// �`�揈�� //

void SceneManager::Draw()
{
    //���݂̃V�[����`��
    ClearDrawScreen();
    nowScene.top()->Draw();

    ScreenFlip();
}

// �V�[���؂�ւ� //

void SceneManager::SceneChange()
{
    if (nowScene.top() != tmpScene)
    {
        //nowScene��tmpScene�ƈقȂ��Ă����������đ��
        nowScene.pop();
        nowScene.push(tmpScene);
    }
}

// �Q�[�����[�v //

void SceneManager::GameLoop()
{
    //�E�B���h�E��������܂Ń��[�v����
    while (ProcessMessage() == 0)
    {
        //�|�[�Y���j���[
        GetHitKeyStateAllEx(keyState);
        if (keyState[KEY_INPUT_ESCAPE] == 1)
        {
            SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            if (nowScene.size() < 2)
            {
                SetMouseDispFlag(TRUE);                                                    //�}�E�X�͕\��
                nowScene.push(PauseMenu::Init());
            }
            else
            {
                SetMouseDispFlag(FALSE);                                                    //�}�E�X�͔�\��
                nowScene.pop();
            }
        }

        //�X�V����
        Update();


        //�`�揈��
        Draw();

        //�V�[���؂�ւ�
        SceneChange();
        if (!nowScene.top())
        {
            break;
        }
    }

    //���[�v�I����̌㏈��
    Finalize();
}