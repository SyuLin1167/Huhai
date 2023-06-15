#include "SceneManager.h"
#include<stack>

#include"../../GameSetting/GameSetting.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"
#include "../TitleScene/Title.h"

// �R���X�g���N�^ //

SceneManager::SceneManager()
    ://nowScene(nullptr)
    timeMgr(nullptr)
    , canLoop(true)
{
}

// �f�X�g���N�^ //

SceneManager::~SceneManager()
{
    //�Ǘ��N���X�̌㏈��
    GameSetting::Finalize();
    ObjManager::Finalize();
    AssetManager::Finalize();

    //�C���X�^���X�̌㏈��
    //delete nowScene;
    delete timeMgr;

    while(!nowScene.empty())
    {
        nowScene.pop();
    }
}

// ���������� //

int SceneManager::Init()
{
    //�Ǘ��N���X�̏�����
    if (GameSetting::Init() == -1)
    {
        return -1;
    }
    ObjManager::Init();
    AssetManager::Init();

    //�C���X�^���X����
    nowScene.push(new Title);
    //nowScene = new Title;
    timeMgr = new TimeManager;

    return 0;
}

// �X�V���� //

void SceneManager::Update()
{
    //�ꎞ�I�ȃV�[��
    SceneBase* tmpScene;

    //�V�[���̍X�V����
    timeMgr->Update();

    //tmpScene�Ɍ��݂̃V�[������
    tmpScene = nowScene.top()->Update(timeMgr->DeltaTime());

    if (!tmpScene)
    {
        canLoop = false;
    }

    if (nowScene.top() != tmpScene)
    {
        //NowScene��tmpScene�ƈقȂ��Ă����������đ��
        //delete nowScene;
        //nowScene = tmpScene;
        nowScene.pop();
        nowScene.push(tmpScene);
    }
}

// �`�揈�� //

void SceneManager::Draw()
{
    //���݂̃V�[����`��
    nowScene.top()->Draw();
}

// �Q�[�����[�v //

void SceneManager::GameLoop()
{
    //���L��������������܂Ń��[�v�\�ɂ���
    //(�E�B���h�E�������邩�AESC�L�[��������邩�C���[�v���s�\�ɂȂ邩)
    while (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 0 || !canLoop)
    {
        //�X�V�������ʂ�������
        Update();
        ClearDrawScreen();

        //�`�揈���㗠��ʂ̓��e��\�`��ɔ��f
        Draw();
        ScreenFlip();
    }
}