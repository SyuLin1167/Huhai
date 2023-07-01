#pragma once

#include"../../GameSetting/GameSetting.h"
#include"../SceneBase/SceneBase.h"
#include "../../UI/Select/Select.h"

/* TitleScene�N���X */
class TitleScene :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TitleScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~TitleScene();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���̃t���[���̃V�[��</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

private:
    int screenGraph;        //��ʕێ��O���t

    class Door* door = nullptr;                 //�h�A
    class Wipe* titleBlend;                //�u�����h���[�h
    class Select* select[SelectTypeSize];       //�I���{�^��
    class Sound* titleSound = nullptr;          //�T�E���h
};
