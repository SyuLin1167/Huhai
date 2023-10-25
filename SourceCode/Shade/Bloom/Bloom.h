#pragma once
#include<DxLib.h>
#include "../../GameSetting/GameSetting.h"

/// <summary>
/// �u���[��
/// </summary>
class Bloom
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Bloom();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Bloom();

    /// <summary>
    /// �X�N���[���Z�b�g
    /// </summary>
    void SetColoerScreen();

    /// <summary>
    /// �`�揀��
    /// </summary>
    void SetBloomGraph();

    /// <summary>
    /// �`��X�V����
    /// </summary>
    void Draw();
private:
    const int DOWN_SCALE = 8;                                       //�t�B���^�[���|����摜�������̂P��
    const int DOWN_SCALE_WIDTH = (SCREEN_WIDTH / DOWN_SCALE);       //�t�B���^�[��������摜�̉���
    const int DOWN_SCALE_HEIGHT = (SCREEN_HEIGHT / DOWN_SCALE);     //�t�B���^�[��������摜�̏c��

    const int GAUSS_PIXEL = 16;       //�ڂ����̃s�N�Z���l
    const int GAUSS_PARAM = 200;      //�K�E�X�̂ڂ����
    const int CLIP_PARAM = 230;       //�N���b�v�p�����[�^�[
    const int CLIP_ALPHA = 250;       //�N���b�v�A���t�@�l

    int ColorScreen;            //���ʂ̕`�挋�ʗp�X�N���[��
    int HighBrightScreen;       //�`�挋�ʂ��獂�P�x���������o���p�X�N���[��
    int DownScaleScreen;        //���P�x�����k���p�X�N���[��
    int GaussScreen;            //�k���摜�ڂ����p�X�N���[��
};

