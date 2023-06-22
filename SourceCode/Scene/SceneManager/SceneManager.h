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
    /// �X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw();

    /// <summary>
    /// �Q�[�����[�v
    /// </summary>
    void GameLoop();

private:
    bool canLoop;                               //���[�v�t���O

    std::stack<class SceneBase*> nowScene;      //���݂̃V�[��

    class TimeManager* timeMgr;                 //�^�C���}�l�[�W���[
};

