#include "SceneManager.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include "../TitleScene/TitleScene.h"
#include"../PauseScene/PauseMenu/PauseMenu.h"
#include "../SaveScene/SaveScene.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
    :pause(new PauseScene)
    , gameSetting(new GameSetting)
    , timeMgr(new TimeManager)
    , pointLightShader(new PointLightShader)
{
    nowScreen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
    //�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
/// <returns></returns>
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

/// <summary>
/// �㏈��
/// </summary>
void SceneManager::Finalize()
{
    //�V�[�����
    while(!nowScene.empty())
    {
        nowScene.pop();
    }
}

/// <summary>
/// �X�V����
/// </summary>
void SceneManager::UpdateScene()
{
    //�V�[���̍X�V����
    storageScene = nowScene.top()->UpdateScene(timeMgr->DeltaTime());
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::DrawScene()
{
    //���݂̃V�[����`��
    ClearDrawScreen();
    nowScene.top()->DrawScene();
    ScreenFlip();
}

/// <summary>
/// �V�[���؂�ւ�
/// </summary>
void SceneManager::SwitchScene()
{
    if (nowScene.top() != storageScene)
    {
        //nowScene��tmpScene�ƈقȂ��Ă����������đ��
        nowScene.pop();
        PauseMenu::ResetTitleButton();
        nowScene.push(storageScene);
    }
}

/// <summary>
/// �|�[�Y���j���[����
/// </summary>
void SceneManager::CheckPauseMenu()
{
    //�|�[�Y���j���[
    GetHitKeyStateAllEx(keyState);
    if (keyState[KEY_INPUT_ESCAPE] == 1)
    {
        SetMousePoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT);
        //�z��̃T�C�Y�Ń��j���[�̕\����؂�ւ���
        if (nowScene.size() < MAX_STACK_SCENE)
        {
            //�Q�[����ʕۑ�
            SetDrawScreen(nowScreen);
            SaveDrawScreenToPNG(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "../Assets/BackGround/GameScene.png", -1);//PNG�ۑ�
            SetDrawScreen(DX_SCREEN_BACK);

            //���j���[��ʕ\��
            SetMouseDispFlag(true);
            nowScene.push(new PauseScene);
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

/// <summary>
/// �Q�[�����[�v
/// </summary>
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