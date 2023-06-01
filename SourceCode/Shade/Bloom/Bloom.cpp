#include "Bloom.h"
#include"../../Object/CharaObject/Camera/CameraFps.h"

Bloom* Bloom::bloom = nullptr;

// @brief Bloom�R���X�g���N�^�[ //

Bloom::Bloom()
    :ColorScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE))
    , HighBrightScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE))
    , DownScaleScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE))
    , GaussScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE))
    , GaussParam(100)
{
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
    SetDrawScreen(bloom->ColorScreen);
}

// @brief Bloom�`�揀�� //

void Bloom::SetBloomGraph() 
{
    //int GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_BRIGHT_CLIP,
    //  int CmpType = �N���b�v�^�C�v( DX_CMP_LESS:CmpParam�ȉ����N���b�v  ����  DX_CMP_GREATER:CmpParam�ȏ���N���b�v ), 
    // int CmpParam = �N���b�v�p�����[�^( 0 �` 255 ), int ClipFillFlag = �N���b�v�����s�N�Z����h��Ԃ����ǂ���( TRUE:�h��Ԃ�  FALSE:�h��Ԃ��Ȃ� ),
    // unsigned int ClipFillColor = �N���b�v�����s�N�Z���ɓh��F�l( GetColor �Ŏ擾���� )( ClipFillFlag �� FALSE �̏ꍇ�͎g�p���Ȃ� ),
    // int ClipFillAlpha = �N���b�v�����s�N�Z���ɓh�郿�l( 0 �` 255 )( ClipFillFlag �� FALSE �̏ꍇ�͎g�p���Ȃ� ) ) ;
    GraphFilterBlt(bloom->ColorScreen, bloom->HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP,
        DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);                                                                               //�`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
    GraphFilterBlt(bloom->HighBrightScreen, bloom->DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);         //���P�x�������W���̂P�ɏk�������摜�𓾂�
    GraphFilterBlt(bloom->DownScaleScreen, bloom->GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, bloom->GaussParam);                                     //�W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���

    SetDrawScreen(DX_SCREEN_BACK);                                                  //�`��Ώۂ𗠉�ʂɂ���
}

void Bloom::Draw()
{
    DrawGraph(0, 0, bloom->ColorScreen, TRUE);

    //---�`�惂�[�h�ݒ�---//
    SetDrawMode(DX_DRAWMODE_BILINEAR);                                              //�`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);                                        //�`��u�����h���[�h�����Z�ɂ���

    //---�ڂ����摜�`��---//
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bloom->GaussScreen, FALSE);         //���P�x�������k�����Ăڂ������摜�`��

    //---�`�惂�[�h�㏈��---//
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);                                    //�u�����h���[�h�𖳂��ɂ���
    SetDrawMode(DX_DRAWMODE_NEAREST);                                               //�`�惂�[�h���j�A���X�g�ɂ���

    //---�r���o�ߕ`��---//
    //DrawExtendGraph(180 * 0 + 24, 320, 180 * 0 + 24 + 160, 120 + 320, bloom->HighBrightScreen, FALSE);
    //DrawExtendGraph(180 * 1 + 24, 320, 180 * 1 + 24 + 160, 120 + 320, bloom->DownScaleScreen, FALSE);
    //DrawExtendGraph(180 * 2 + 24, 320, 180 * 2 + 24 + 160, 120 + 320, bloom->GaussScreen, FALSE);
}