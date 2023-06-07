#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Collision/Collision.h"

/*�E�o�V�[���N���X*/
class EscapeScene:public SceneBase
{
public:
    /// <summary>
    /// EscapeScene�R���X�g���N�^
    /// </summary>
    EscapeScene();

    /// <summary>
    /// EscapeScene�f�X�g���N�^
    /// </summary>
    ~EscapeScene();

    /// <summary>
    /// EscapeScene�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���݂̃V�[���̃|�C���^</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// EscapeScene�`�揈��
    /// </summary>
    void Draw()override;

private:
    class BlendMode* escBlend;
    class Sound* escSound;
};

