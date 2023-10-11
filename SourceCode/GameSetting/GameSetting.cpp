#include "GameSetting.h"
#include <DxLib.h>
#include"../Scene/SceneBase/SceneBase.h"

//�̂��ɉ�ʃT�C�Y�̒萔��ObjBase����SceneBase�Ɉړ�������
#include"../Object/ObjectBase/ObjBase.h"



// ���������� //

int GameSetting::Init()
{
    //���O�̔�\��
    SetOutApplicationLogValidFlag(false);

    //�E�B���h�E�̐ݒ�
    ChangeWindowMode(true);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);
    SetWindowSizeExtendRate(1.0);
    SetMainWindowText("Huhai");

    //�A���`�G�C���A�X��ݒ�
    SetFullSceneAntiAliasingMode(4, 2);

    // Direct3D9Ex ���g�p����
    SetUseDirect3DVersion(DX_DIRECT3D_9EX);

    if (DxLib_Init() == -1)
    {
        //���C�u�����������ŃG���[���N������I��
        return -1;
    }

    if (GetValidShaderVersion() < 300)
    {
        //�V�F�[�_�[���f���R�D�O���g�p�ł��Ȃ��ꍇ�͏I��
        DxLib_End();
        return 0;
    }

    //�`���𗠉�ʂɕύX
    SetDrawScreen(DX_SCREEN_BACK);

    //Z�o�b�t�@�ݒ�
    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);

    //�W�����C�g�𖳌���
    SetLightEnable(false);
    SetUsePixelLighting(true);

    //����������
    return 0;
}

// �㏈�� //

void GameSetting::Finalize()
{
    //Dx���C�u�����̌㏈��
    DxLib_End();
}

