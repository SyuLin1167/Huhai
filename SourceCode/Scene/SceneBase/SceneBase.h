#pragma once

#include <Dxlib.h>
#include<memory>
#include"../../GameSetting/GameSetting.h"
#include"../../BlendMode/BlendMode.h"
#include"../../Asset/Sound/Sound.h"

/// <summary>
/// SceneBase�N���X
/// </summary>
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
    /// <param name="deltaTime">:�f���^�^�C��</param>
    /// <returns>���݂̃V�[��</retdeltaTimeurns>
    virtual SceneBase* UpdateScene(const float deltaTime) = 0;

    /// <summary>
    /// �V�[���̕`��
    /// </summary>
    virtual void DrawScene() = 0;

protected:
    int bgHandle;       //�w�i�摜�n���h��
    int bgX;            //�w�i���WX
    int bgY;            //�w�i���WY

    const int BLACK_SCREEN_COLOR; //�X�N���[���̐F(�u���b�N)

    std::unique_ptr<BlendMode> blendMode;       //�u�����h���[�h
    std::unique_ptr<Sound> sound;               //�T�E���h
};
