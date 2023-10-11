#include "SceneManager.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include "../TitleScene/TitleScene.h"
#include"../PauseMenu/PauseMenu.h"
#include "../SaveScene/SaveScene.h"


// �R���X�g���N�^ //

SceneManager::SceneManager()
{
    //�C���X�^���X����
    gameSetting.reset(new GameSetting);
    timeMgr.reset(new TimeManager);
    pointLightShader.reset(new PointLightShader);

    nowScreen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// �f�X�g���N�^ //

SceneManager::~SceneManager()
{
    //�����Ȃ�
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

    //�V�[���֘A�̃N���X������
    SaveScene::CreateInstance();
    PauseMenu::CreateInstance();

    //�����V�[���ݒ�
    nowScene.push(new TitleScene);
    SetDrawBright(255, 255, 255);
    return 0;
}

// �㏈�� //

void SceneManager::Finalize()
{
    //�V�[�����
    while(!nowScene.empty())
    {
        nowScene.pop();
    }
}

// �X�V���� //

void SceneManager::UpdateScene()
{
    //�V�[���̍X�V����
    storageScene = nowScene.top()->UpdateScene(timeMgr->DeltaTime());
}

// �`�揈�� //

void SceneManager::DrawScene()
{
    //���݂̃V�[����`��
    ClearDrawScreen();
    nowScene.top()->DrawScene();
    ScreenFlip();
}

// �V�[���؂�ւ� //

void SceneManager::SwitchScene()
{
    if (nowScene.top() != storageScene)
    {
        //nowScene��tmpScene�ƈقȂ��Ă����������đ��
        nowScene.pop();
        nowScene.push(storageScene);
    }
}

// �|�[�Y���j���[���� //

void SceneManager::CheckPauseMenu()
{
    //�|�[�Y���j���[
    GetHitKeyStateAllEx(keyState);
    if (keyState[KEY_INPUT_ESCAPE] == 1)
    {
        SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        //�z��̃T�C�Y�Ń��j���[�̕\����؂�ւ���
        if (nowScene.size() < MAX_STACK_SCENE)
        {
            //�Q�[����ʕۑ�
            SetDrawScreen(nowScreen);
            SaveDrawScreenToPNG(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "../Assets/BackGround/GameScene.png", -1);//PNG�ۑ�
            SetDrawScreen(DX_SCREEN_BACK);

            //���j���[��ʕ\��
            SetMouseDispFlag(true);
            nowScene.push(PauseMenu::GetPauseMenuInstance());
            DeleteGraph(nowScreen);

        }
        else
        {
            SetMouseDispFlag(false);
            nowScene.pop();
        }
    }

    //�^�C�g����ʈړ������j���[��ʂ�����
    if (PauseMenu::BackToTitle() && nowScene.size() >= MAX_STACK_SCENE)
    {
        nowScene.pop();
    }
}

// �Q�[�����[�v //

void SceneManager::GameLoop()
{
    //�E�B���h�E��������܂Ń��[�v����
    while (ProcessMessage() == 0)
    {
        //�|�[�Y���j���[
        CheckPauseMenu();

        //�X�V����
        UpdateScene();

        //�`�揈��
        DrawScene();

        //�V�[���؂�ւ�
        SwitchScene();

        if (!nowScene.top())
        {
            break;
        }
    }

    //���[�v�I����̌㏈��
    Finalize();
}