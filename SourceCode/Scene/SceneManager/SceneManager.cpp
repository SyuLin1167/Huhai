#include "SceneManager.h"

#include"../../GameSetting/GameSetting.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"
#include "../TitleScene/Title.h"
#include "../Save/Save.h"

// �R���X�g���N�^ //

SceneManager::SceneManager()
    :timeMgr(nullptr)
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
    SaveScene::Init();

    //�C���X�^���X����
    timeMgr = new TimeManager;

    //�����V�[���ݒ�
    nowScene.push(new Title);

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