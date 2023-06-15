#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"

/* PlayScene�N���X */
class Play :public SceneBase
{

public:
    /// <summary>
    /// PlayScene�R���X�g���N�^
    /// </summary>
    Play();

    /// <summary>
    /// PlayScene�f�X�g���N�^
    /// </summary>
    ~Play();

    /// <summary>
    /// PlayScene�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���݂̃V�[���̃|�C���^</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// PlayScene�̕`��
    /// </summary>
    void Draw()override;

private:
    bool sceneChange;
};