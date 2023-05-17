#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"
#include"../../BlendMode/BlendMode.h"


/* �^�C�g���V�[���̃N���X */
class Title :public SceneBase
{
    class Door* door = nullptr;
    class Select* select = nullptr;
    class BlendMode* titleBlend;

public:
    /// <summary>
    /// TitleScene�R���X�g���N�^
    /// </summary>
    Title();

    /// <summary>
    /// TitleScene�f�X�g���N�^
    /// </summary>
    ~Title();

    /// <summary>
    /// TitleScene�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���݂̃V�[���̃|�C���^</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// TitleScene�V�[���̕`��
    /// </summary>
    void Draw()override;

private: 
    int graph;
    bool fadeLock;
};
