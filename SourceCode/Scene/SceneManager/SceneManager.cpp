#include "SceneManager.h"

#include"../../GameSetting/GameSetting.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"
#include "../TitleScene/Title.h"
#include"../PauseMenu/PauseMenu.h"
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

    nowScreen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);

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

    //�V�[���֘A�̃N���X������
    SaveScene::Init();
    PauseMenu::Init();

    //�����V�[���ݒ�
    nowScene.push(new TitleScene);
    SetDrawBright(255, 255, 255);
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

// �|�[�Y���j���[���� //

void SceneManager::Pause()
{
    //�|�[�Y���j���[
    GetHitKeyStateAllEx(keyState);
    if (keyState[KEY_INPUT_ESCAPE] == 1)
    {
        SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        //�z��̃T�C�Y�Ń��j���[�̕\����؂�ւ���
        if (nowScene.size() < 2)
        {
            //�Q�[����ʕۑ�
            SetDrawScreen(nowScreen);
            SaveDrawScreenToPNG(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "../Assets/BackGround/GameScene.png", -1);//PNG�ۑ�
            SetDrawScreen(DX_SCREEN_BACK);

            //���j���[��ʕ\��
            SetMouseDispFlag(true);
            nowScene.push(PauseMenu::Init());
            DeleteGraph(nowScreen);
        }
        else
        {
            SetMouseDispFlag(false);
            nowScene.pop();
        }
    }

    //�^�C�g����ʈړ������j���[��ʂ�����
    if (PauseMenu::BackToTitle() && nowScene.size() > 1)
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
        Pause();

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