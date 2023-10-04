#pragma once

#include<stack>
#include<memory>
#include"../../GameSetting/GameSetting.h"
#include"../../Time/TimeManager.h"
#include"../../Shade/PointLight/PointLightShader.h"

/*SceneManager�N���X*/
class SceneManager
{

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneManager();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SceneManager();

    /// <summary>
    /// ����������
    /// </summary>
    int Init();

    /// <summary>
    /// �㏈��
    /// </summary>
    void Finalize();

    /// <summary>
    /// �X�V����
    /// </summary>
    void UpdateScene();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void DrawScene();

    /// <summary>
    /// �V�[���؂�ւ�
    /// </summary>
    void SwitchScene();

    /// <summary>
    /// �|�[�Y���j���[���菈��
    /// </summary>
    void CheckPauseMenu();

    /// <summary>
    /// �Q�[�����[�v
    /// </summary>
    void GameLoop();

private:
    int keyState[256] = { 0 };                  //�L�[�X�e�[�^�X
    int nowScreen;                              //���݂̉��

    std::stack<class SceneBase*> nowScene;      //���݂̃V�[��
    SceneBase* tmpScene;                        //�ꎞ�I�ȃV�[��

    std::unique_ptr<GameSetting> gameSetting;             //�Q�[���Z�b�e�B���O
    std::unique_ptr<TimeManager> timeMgr;                 //�^�C���}�l�[�W���[
    std::unique_ptr<PointLightShader> pointLightShader;           //�|�C���g���C�g�V�F�[�_�[
};

