#include"DxLib.h"
#include"Scene/SceneManager/SceneManager.h"
#include"Object/ObjectManager/ObjManager.h"
#include"Asset/AssetManager/AssetManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{

	SetGraphMode(ScreenWidth, ScreenHeight, ColorBit);		//��ʃ��[�h�̃Z�b�g


	//---DX���C�u����������---//
	SetUseDirect3DVersion(DX_DIRECT3D_11);					//�g�p����Direct3D�̃o�[�W�����ݒ�
	ChangeWindowMode(TRUE);									//�E�B���h�E���[�h�̕ύX
	if (DxLib_Init() == -1)
	{
		return -1;											//�G���[���N������I��
	}

	//---Z�o�b�t�@�ݒ�---//
	SetUseZBuffer3D(TRUE);									//Z�o�b�t�@��L���ɂ���
	SetWriteZBuffer3D(TRUE);								//Z�o�b�t�@�G�̏������݂�L���ɂ���

	//---�Ǘ��N���X�̏���������---//
	SceneManager* sceneManager = new SceneManager();
	ObjManager::Init();
	AssetManager::Init();

	//�W�����C�g�𖳌���
	//SetLightEnable(FALSE);

	// �w���Ƀ}�C�i�X�����̃f�B���N�V���i���^�C�v�̃��C�g�̍쐬
	int LightHandle = CreatePointLightHandle(VGet(0.0f, 50.0f, 0.0f),100.0f,0.0f,0.0f,0.002f);
	
	

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