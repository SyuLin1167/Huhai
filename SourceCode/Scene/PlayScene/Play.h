#pragma once
#include <DxLib.h>
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"

class CameraFps;
class Player;
class Enemy;
class Collision;
class Grid;

/* �v���C�V�[���̃N���X */
class Play :public SceneBase
{
    CameraFps* camFps = nullptr;
    Player* player = nullptr;                     //�v���C���[
    Enemy* enemy = nullptr;                       //�G�l�~�[
    Collision* col = nullptr;
    Grid* grid=nullptr;

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

};