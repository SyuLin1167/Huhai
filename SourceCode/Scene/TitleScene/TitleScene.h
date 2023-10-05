#pragma once

#include"../SceneBase/SceneBase.h"
#include "../../UI/Select/SelectType.h"

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
    SceneBase* UpdateScene(const float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void DrawScene()override;

private:
    const int TITLE_POS_X = 180;                //�^�C�g�����S���WX
    const int TITLE_POS_Y = 150;                //�^�C�g�����S���WY
    const int TITLE_SIZE_X = 450;               //�^�C�g�����S�T�C�YX
    const int TITLE_SIZE_Y = 200;               //�^�C�g�����S�T�C�YY

    int screenGraph;                            //��ʕێ��O���t

    class Door* door = nullptr;                 //�h�A
    class Select* select[SelectTypeSize];       //�I���{�^��
};
