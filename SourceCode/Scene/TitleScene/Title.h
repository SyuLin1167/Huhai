#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"
#include"../../BlendMode/BlendMode.h"
#include"../../UI/Select/SelectType.h"


    /* TitleScene�N���X */
class Title :public SceneBase
{
    class Door* door = nullptr;
    class BlendMode* titleBlend;
    class Select* select[TypeSize];
    class Sound* sound = nullptr;

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Title();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Title();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���݂̃V�[���̃|�C���^</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// �V�[���̕`��
    /// </summary>
    void Draw()override;

private:
    int graph;
    bool fadeLock;
};
