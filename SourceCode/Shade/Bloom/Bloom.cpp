#include "Bloom.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../GameSetting/GameSetting.h"

// �R���X�g���N�^ //

Bloom::Bloom()
    :ColorScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE))
    , HighBrightScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE))
    , DownScaleScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE))
    , GaussScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE))
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
    SetCameraNearFar(0.1f, 400.0f);
}

// �`�揀�� //

void Bloom::SetBloomGraph() 
{
    //�`�挋�ʂ��獂�P�x�����𔲂��o���Ăڂ���
    GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP,
        DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);
    GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);
    GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussParam);

    //�`��Ώۂ𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);
    ClearDrawScreenZBuffer();
}

// �`�揈�� //

void Bloom::Draw()
{
    //�ʏ�̉�ʂ�`��
    DrawGraph(0, 0, ColorScreen, FALSE);

    //�ڂ����摜�`��
    SetDrawMode(DX_DRAWMODE_BILINEAR);
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    SetDrawMode(DX_DRAWMODE_NEAREST);
}