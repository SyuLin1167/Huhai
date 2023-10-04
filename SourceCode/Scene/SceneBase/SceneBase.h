#pragma once

#include <Dxlib.h>
#include<memory>
#include"../../BlendMode/BlendMode.h"
#include"../../Asset/Sound/Sound.h"

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
    virtual SceneBase* UpdateScene(const float deltaTime) = 0;

    /// <summary>
    /// �V�[���̕`��
    /// </summary>
    virtual void DrawScene() = 0;

protected:
    int BgHandle;       //�w�i�摜�n���h��
    int BgX;            //�w�i���WX
    int BgY;            //�w�i���WY

    std::unique_ptr<BlendMode> blendMode;       //�u�����h���[�h
    std::unique_ptr<Sound> sound;               //�T�E���h
};
