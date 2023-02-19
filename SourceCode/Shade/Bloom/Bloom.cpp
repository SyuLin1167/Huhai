#include "Bloom.h"
#include"../../Object/CharaObject/Camera/CameraFps.h"

Bloom* Bloom::bloom = nullptr;
int Bloom::GaussParam;
int Bloom::ColorScreen;
int Bloom::HighBrightScreen;
int Bloom::DownScaleScreen;
int Bloom::GaussScreen;

// @brief Bloom�R���X�g���N�^�[ //

Bloom::Bloom()
{
    bloom = nullptr;

    //---�X�N���[���̍쐬---//
    ColorScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);                   //�ʏ�̕`�挋�ʂ��������ރX�N���[���쐬
    HighBrightScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);              //��̌��ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[���쐬
    DownScaleScreen = MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE);        //���P�x�������k���������ʂ��������ރX�N���[���쐬
    GaussScreen = MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE);            //�k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[���쐬

    SetBackgroundColor(255, 255, 255);                                              //ClearDrawScreen���ɃZ�b�g�����F�ŉ�ʂ�h��Ԃ�

    GaussParam = 500;                                                               //�K�E�X�̂ڂ����
}

// @briefb Bloom�f�X�g���N�^�[ //

Bloom::~Bloom()
{
    bloom = nullptr;
}

// @brief Bloom���������� //

void Bloom::Init()
{
    if (!bloom)
    {
        bloom = new Bloom;
    }
}

// @brief �X�N���[���Z�b�g //

void Bloom::SetColoerScreen()
{
    SetDrawScreen(ColorScreen);
}

// @brief Bloom�`��X�V���� //

void Bloom::DrawUpdate() 
{
    GraphFilterBlt(ColorScreen, HighBrightScreen,
        DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE,
        GetColor(0, 0, 0), 255);                                                    //�`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
    GraphFilterBlt(HighBrightScreen,DownScaleScreen,
        DX_GRAPH_FILTER_DOWN_SCALE,DOWN_SCALE);                                     //���P�x�������W���̂P�ɏk�������摜�𓾂�
    GraphFilterBlt(DownScaleScreen, GaussScreen,
        DX_GRAPH_FILTER_GAUSS, 16, GaussParam);                                     //�W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���

    SetDrawScreen(DX_SCREEN_BACK);                                                  //�`��Ώۂ𗠉�ʂɂ���
    ClearDrawScreenZBuffer();

    //---�`�惂�[�h�ݒ�---//
    SetDrawMode(DX_DRAWMODE_BILINEAR);                                              //�`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);                                        //�`��u�����h���[�h�����Z�ɂ���

    //---�ڂ����摜�`��---//
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);         //���P�x�������k�����Ăڂ������摜�`��
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);         //��ʂ����ς���2��`�悷��
    
    //---�`�惂�[�h�㏈��---//
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);                                    //�u�����h���[�h�𖳂��ɂ���
    SetDrawMode(DX_DRAWMODE_NEAREST);                                               //�`�惂�[�h���j�A���X�g�ɂ���

    //---�r���o�ߕ`��---//
    DrawExtendGraph(180 * 0 + 24, 320, 180 * 0 + 24 + 160, 120 + 320, HighBrightScreen, FALSE);
    DrawExtendGraph(180 * 1 + 24, 320, 180 * 1 + 24 + 160, 120 + 320, DownScaleScreen, FALSE);
    DrawExtendGraph(180 * 2 + 24, 320, 180 * 2 + 24 + 160, 120 + 320, GaussScreen, FALSE);
}