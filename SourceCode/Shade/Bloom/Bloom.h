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
    /// �u���[���̕`�揀��
    /// </summary>
    static void SetBloomGraph();

    /// <summary>
    /// Bloom�`��X�V����
    /// </summary>
    static void Draw();
private:
    /// <summary>
    /// �R���X�g���N�^�[(�V���O���g��)
    /// </summary>
    Bloom();

    /// <summary>
    /// �f�X�g���N�^�[
    /// </summary>
	~Bloom();

    int GaussParam;             //�K�E�X�̂ڂ����
    int ColorScreen;            //���ʂ̕`�挋�ʂ��������ރX�N���[��
    int HighBrightScreen;       //���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
    int DownScaleScreen;        //���P�x�������k���������ʂ��������ރX�N���[��
    int GaussScreen;            //�k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��

    static Bloom* bloom;               //Bloom�̎���
};

