#pragma once
#include<stack>

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
    void Update();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw();

    /// <summary>
    /// �V�[���؂�ւ�
    /// </summary>
    void SceneChange();

    /// <summary>
    /// �Q�[�����[�v
    /// </summary>
    void GameLoop();

private:
    int keyState[256] = { 0 };                  //�L�[�X�e�[�^�X

    std::stack<class SceneBase*> nowScene;      //���݂̃V�[��
    SceneBase* tmpScene;                        //�ꎞ�I�ȃV�[��

    class GameSetting* gameSetting;             //�Q�[���Z�b�e�B���O
    class TimeManager* timeMgr;                 //�^�C���}�l�[�W���[
};

