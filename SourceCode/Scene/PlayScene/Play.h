#pragma once
#include <DxLib.h>
#include"../SceneBase/SceneBase.h"

const float CameraNear = 1.0f;       //�J�����̕`��͈�(��)
const float CameraFar = 2000.0f;     //�J�����̕`��͈�(��)

class Player;
class Enemy;

/* �v���C�V�[���̃N���X */
class Play :public SceneBase
{
    Player* player = nullptr;                     //�v���C���[
    Enemy* enemy = nullptr;                       //�G�l�~�[

public:
    /// <summary>
    /// �R���X�g���N�^�[
    /// </summary>
    Play();

    /// <summary>
    /// �f�X�g���N�^�[
    /// </summary>
    ~Play();

    /// <summary>
    /// PlayScene�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���݂̃V�[���̃|�C���^</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// �v���C�V�[���̕`��
    /// </summary>
    void Draw()override;

private:
    //---�n�ʃO���b�h�`��֘A---//(�̂��ɃQ�[���I�u�W�F�N�g�Ɉڍs)
    VECTOR p1;
    VECTOR p2;
    const float GridAllSize = 100.0f;
    const int DivideNum = 10;
    const float GridSpace = GridAllSize / DivideNum;
};