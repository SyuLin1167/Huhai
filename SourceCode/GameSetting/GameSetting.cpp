#include "GameSetting.h"
#include <DxLib.h>
#include"../Scene/SceneBase/SceneBase.h"

//�̂��ɉ�ʃT�C�Y�̒萔��ObjBase����SceneBase�Ɉړ�������
#include"../Object/ObjectBase/ObjectBase.h"

//���g�ւ̃|�C���^��`
GameSetting* GameSetting::gameSetting = nullptr;

// ���������� //

int GameSetting::Init()
{
    //�C���X�^���X�̒��g���󂾂����璆�g��錾����
    if (!gameSetting)
    {
        gameSetting = new GameSetting;
    }

    //�E�B���h�E�̐ݒ�
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);
    SetWindowSizeExtendRate(1.0);

    //�g�p����Direct3D�̃o�[�W�����ݒ�
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    //�A���`�G�C���A�X��ݒ�
    SetFullSceneAntiAliasingMode(4, 2);

    if (DxLib_Init() == -1)
    {
        //���C�u�����������ŃG���[���N������I��
        return -1;
    }

    //�`���𗠉�ʂɕύX
    SetDrawScreen(DX_SCREEN_BACK);

    //Z�o�b�t�@�ݒ�
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    //�W�����C�g�𖳌���
    SetLightEnable(FALSE);

    //����������
    return 0;
}

// �㏈�� //

void GameSetting::Finalize()
{
    //Dx���C�u�����̌㏈��
    DxLib_End();

    //�C���X�^���X�̌㏈��
    delete gameSetting;
}

