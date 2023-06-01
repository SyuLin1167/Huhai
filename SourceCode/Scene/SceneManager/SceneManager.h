#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"


/*�V�[���}�l�[�W���[�̃N���X*/
class SceneManager
{
private:
    SceneBase* nowScene;
    TimeManager* timeManager;

public:
    /// <summary>
    /// �R���X�g���N�^�[
    /// </summary>
    SceneManager();

    /// <summary>
    /// �f�X�g���N�^�[
    /// </summary>
    ~SceneManager();

    /// <summary>
    /// SceneManager�X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// ���݂̃V�[���̕`��
    /// </summary>
    void Draw();

    bool IsLoop() { return isLoop; }
private:
    bool isLoop;
};

