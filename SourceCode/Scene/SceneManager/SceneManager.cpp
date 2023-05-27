#include "SceneManager.h"
#include "../TitleScene/Title.h"
#include "../PlayScene/Play.h"
#include"../../Shade/Bloom/Bloom.h"

// @brief SceneManager�R���X�g���N�^�[ //

SceneManager::SceneManager()
    :nowScene(new Title())
    , timeManager(new TimeManager)
{
    Bloom::Init();
}

// @brief SceneManager�f�X�g���N�^�[ //

SceneManager::~SceneManager()
{
    delete nowScene;
}

// @brief�@SceneManager�X�V���� //

void SceneManager::Update()
{
    SceneBase* tmpScene;     //�ꎞ�I�ȃV�[��
    timeManager->Update();
    Bloom::SetColoerScreen();
    //---�V�[���̍X�V����---//
    tmpScene = nowScene->Update(timeManager->DeltaTime());     //tmpScene�Ɍ��݂̃V�[������
    if (nowScene != tmpScene)                                  //���݂̃V�[����tmpScene�ƈقȂ��Ă�����
    {
        delete nowScene;                                       //���݂̃V�[�������
        nowScene = tmpScene;                                   //���݂̃V�[����tmpScene����
    }
}

// @brief ���݂̃V�[���̕`�� //

void SceneManager::Draw()
{
    nowScene->Draw();
    Bloom::DrawUpdate();
}