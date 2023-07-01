#pragma once
#include"../SceneBase/SceneBase.h"

/*RoomScene�N���X*/
class RoomScene :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    RoomScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~RoomScene();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���t���[���̃V�[��</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

private:
    class Wipe* roomBlend;      //�u�����h���[�h
    class Sound* roomSound;     //�T�E���h
};
