#pragma once

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
    /// NowScene�X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// NowScene�`�揈��
    /// </summary>
    void Draw();

    /// <summary>
    /// �Q�[�����[�v
    /// </summary>
    void GameLoop();

private:
    bool canLoop;
    std::stack<class SceneBase*> nowScene;
    //class SceneBase* nowScene;
    class TimeManager* timeMgr;
};

