#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

/*RoomScene�N���X*/
class Room :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Room();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Room();

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
    class BlendMode* roomBlend;    //�u�����h���[�h
};
