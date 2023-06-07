#pragma once
#include <Dxlib.h>

//�J���[�r�b�g��
const int ColorBit = 16;

/*SceneBase�N���X*/
class SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneBase();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneBase();

    /// <summary>
    /// Scene�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���݂̃V�[���̃|�C���^</returns>
    virtual SceneBase* Update(float deltaTime) = 0;

    /// <summary>
    /// �V�[���̕`��
    /// </summary>
    virtual void Draw() = 0;

protected:
    //�w�i�摜�n���h��
    int BgHandle;

    //�w�i���W
    int BgX;
    int BgY;

};

