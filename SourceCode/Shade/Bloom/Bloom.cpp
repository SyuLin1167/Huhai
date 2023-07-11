#include "Bloom.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../GameSetting/GameSetting.h"
#include"../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"

// �R���X�g���N�^ //

Bloom::Bloom()
    :ColorScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false))
    , HighBrightScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false))
    , DownScaleScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, false))
    , GaussScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, false))
    , GaussParam(200)
{
    SetBackgroundColor(0, 0, 0);
}

// �f�X�g���N�^ //

Bloom::~Bloom()
{
}


// �X�N���[���Z�b�g //

void Bloom::SetColoerScreen()
{
    SetDrawScreen(ColorScreen);
    SetCameraNearFar(CameraNear, CameraFar);
}

// �`�揀�� //

void Bloom::SetBloomGraph() 
{
    //�`�挋�ʂ��獂�P�x�����𔲂��o���Ăڂ���
    GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP,
        DX_CMP_LESS, 230, true, GetColor(0, 0, 0), 255);
    GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);
    GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussParam);

    //�`��Ώۂ𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);
}

// �`�揈�� //

void Bloom::Draw()
{
    //�ʏ�̉�ʂ�`��
    DrawGraph(0, 0, ColorScreen, true);

    //�ڂ����摜�`��
    SetDrawMode(DX_DRAWMODE_BILINEAR);
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, false);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    SetDrawMode(DX_DRAWMODE_NEAREST);
}