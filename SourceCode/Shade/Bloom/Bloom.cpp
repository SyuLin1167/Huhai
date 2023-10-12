#include "Bloom.h"

#include"../../GameSetting/GameSetting.h"
#include"../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include"../../Scene/PauseMenu/PauseMenu.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bloom::Bloom()
    :ColorScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false))
    , HighBrightScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false))
    , DownScaleScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, false))
    , GaussScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, false))
    , GaussParam(200)
{
    SetBackgroundColor(0, 0, 0);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Bloom::~Bloom()
{
    //�����Ȃ�
}


/// <summary>
/// �X�N���[���Z�b�g
/// </summary>
void Bloom::SetColoerScreen()
{
    if (PauseMenu::HasStatus("Bloom"))
    {
        SetDrawScreen(ColorScreen);
    }
    SetCameraNearFar(CameraNear, CameraFar);
}

/// <summary>
/// �`�揀��
/// </summary>
void Bloom::SetBloomGraph() 
{
    if (PauseMenu::HasStatus("Bloom"))
    {
        //�`�挋�ʂ��獂�P�x�����𔲂��o���Ăڂ���
        GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP,
            DX_CMP_LESS, 230, true, GetColor(0, 0, 0), 255);
        GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);
        GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussParam);

        //�`��Ώۂ𗠉�ʂɂ���
        SetDrawScreen(DX_SCREEN_BACK);
    }
}

/// <summary>
/// �`��X�V����
/// </summary>
void Bloom::Draw()
{
    if (PauseMenu::HasStatus("Bloom"))
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
}