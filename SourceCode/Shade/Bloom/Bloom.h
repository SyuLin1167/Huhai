#pragma once
#include<DxLib.h>

#include"../../Object/ObjectBase/ObjectBase.h"

#define DOWN_SCALE 8                                    //�t�B���^�[���|����摜�������̂P��
#define DOWN_SCALE_WIDTH (SCREEN_WIDTH/DOWN_SCALE)         //�t�B���^�[��������摜�̉���
#define DOWN_SCALE_HEIGHT (SCREEN_HEIGHT/DOWN_SCALE)       //�t�B���^�[��������摜�̏c��

/*�u���[���̃N���X*/
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

    int GaussParam;             //�K�E�X�̂ڂ����
    int ColorScreen;            //���ʂ̕`�挋�ʗp�X�N���[��
    int HighBrightScreen;       //�`�挋�ʂ��獂�P�x���������o���p�X�N���[��
    int DownScaleScreen;        //���P�x�����k���p�X�N���[��
    int GaussScreen;            //�k���摜�ڂ����p�X�N���[��
};

