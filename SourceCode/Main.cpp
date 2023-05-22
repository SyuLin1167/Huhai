#include<DxLib.h>
#include"Scene/SceneManager/SceneManager.h"
#include"Object/ObjectManager/ObjManager.h"
#include"Asset/AssetManager/AssetManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);    //��ʃ��[�h�̃Z�b�g
    SetWindowSizeExtendRate(1.0);

    SetUseDirect3DVersion(DX_DIRECT3D_11);					//�g�p����Direct3D�̃o�[�W�����ݒ�
    ChangeWindowMode(TRUE);									//�E�B���h�E���[�h�̕ύX
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);			//��ʂ̉𑜓x�ƐF�r�b�g�Ɛ[�x��ݒ�

	SetFullSceneAntiAliasingMode(4, 2);                     //�A���`�G�C���A�X��ݒ�

    //---DX���C�u����������---//
	if (DxLib_Init() == -1)
	{
		return -1;											//�G���[���N������I��
	}

	SetDrawScreen(DX_SCREEN_BACK);                          //�`���𗠉�ʂɕύX

	//---Z�o�b�t�@�ݒ�---//
	SetUseZBuffer3D(TRUE);									//Z�o�b�t�@��L���ɂ���
	SetWriteZBuffer3D(TRUE);								//Z�o�b�t�@�G�̏������݂�L���ɂ���

	//---�Ǘ��N���X�̏���������---//
	SceneManager* sceneManager = new SceneManager;
	AssetManager::Init();
	ObjManager::Init();

	//�W�����C�g�𖳌���
	SetLightEnable(FALSE);
	SetBackgroundColor(150, 150, 150);

	//---�V�[�����[�v---//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)			//�E�B���h�E�������邩�AESC�L�[���������܂Ŏ��s
	{
		sceneManager->Update();								//�X�V����
		ClearDrawScreen();									//��ʂ�������

		sceneManager->Draw();								//�`�揈��
		ScreenFlip();										//����ʂ̓��e��\�`��ɔ��f
	}

	//---�Ǘ��N���X�̌㏈��---//
	ObjManager::Finalize();
	AssetManager::Finalize();

	DxLib_End();											//Dx���C�u�����̌㏈��

	return 0;												//�\�t�g�̏I��
}