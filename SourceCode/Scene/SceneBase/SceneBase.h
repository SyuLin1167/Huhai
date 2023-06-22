#pragma once
#include <Dxlib.h>

//�J���[�r�b�g��
constexpr int ColorBit = 16;

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
    /// <returns>���݂̃V�[��</retdeltaTimeurns>
    virtual SceneBase* Update(float) = 0;

    /// <summary>
    /// �V�[���̕`��
    /// </summary>
    virtual void Draw() = 0;

protected:
    int BgHandle;       //�w�i�摜�n���h��
    int BgX;            //�w�i���WX
    int BgY;            //�w�i���WY
};

class Save
{

};
