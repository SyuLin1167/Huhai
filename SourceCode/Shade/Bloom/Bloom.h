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
    /// Bloom����������
    /// </summary>
    static void Init();

    /// <summary>
    /// �X�N���[���Z�b�g
    /// </summary>
    static void SetColoerScreen();

    /// <summary>
    /// Bloom�`��X�V����
    /// </summary>
    static void DrawUpdate();
private:
    /// <summary>
    /// �R���X�g���N�^�[(�V���O���g��)
    /// </summary>
    Bloom();

    /// <summary>
    /// �f�X�g���N�^�[
    /// </summary>
	~Bloom();

    static int GaussParam;             //�K�E�X�̂ڂ����
    static int ColorScreen;            //���ʂ̕`�挋�ʂ��������ރX�N���[��
    static int HighBrightScreen;       //���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
    static int DownScaleScreen;        //���P�x�������k���������ʂ��������ރX�N���[��
    static int GaussScreen;            //�k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��

    static Bloom* bloom;               //Bloom�̎���
};

