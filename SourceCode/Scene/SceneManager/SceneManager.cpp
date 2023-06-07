#include "SceneManager.h"
#include "../TitleScene/Title.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"

// �R���X�g���N�^ //

SceneManager::SceneManager()
    :nowScene(nullptr)
    , timeMgr(nullptr)
    , isLoop(true)
{
    //�Ǘ��N���X�̏�����
    AssetManager::Init();
    ObjManager::Init();
}

// �f�X�g���N�^ //

SceneManager::~SceneManager()
{
    //�C���X�^���X�̌㏈��
    delete nowScene;

    //�Ǘ��N���X�̌㏈��
    ObjManager::Finalize();
    AssetManager::Finalize();
}

// ���������� //

int SceneManager::Init()
{
    //��ʃ��[�h�̃Z�b�g
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);
    SetWindowSizeExtendRate(1.0);

    //�g�p����Direct3D�̃o�[�W�����ݒ�
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    //�E�B���h�E���[�h�̕ύX
    ChangeWindowMode(TRUE);

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

    //�C���X�^���X����
    nowScene = new Title;
    timeMgr = new TimeManager;

    //����������
    return 0;
}

// NowScene�X�V���� //

void SceneManager::Update()
{
    //�ꎞ�I�ȃV�[��
    SceneBase* tmpScene;

    //�V�[���̍X�V����
    timeMgr->Update();

    //tmpScene�Ɍ��݂̃V�[������
    tmpScene = nowScene->Update(timeMgr->DeltaTime());

    if (!tmpScene)
    {
        isLoop = false;
    }

    if (nowScene != tmpScene)
    {
        //NowScene��tmpScene�ƈقȂ��Ă�����NowScene�����
        delete nowScene;

        //���݂̃V�[����tmpScene����
        nowScene = tmpScene;
    }
}

// NowScene�`�揈�� //

void SceneManager::Draw()
{
    //���݂̃V�[����`��
    nowScene->Draw();
}

// �Q�[�����[�v //

void SceneManager::GameLoop()
{
    //���L��������������܂Ń��[�v�\�ɂ���
    //(�E�B���h�E�������邩�AESC�L�[��������邩�C���[�v���s�\�ɂȂ邩)
    while (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 0 || !isLoop)
    {
        //�X�V�������ʂ�������
        Update();
        ClearDrawScreen();

        //�`�揈���㗠��ʂ̓��e��\�`��ɔ��f
        Draw();
        ScreenFlip();
    }

    //Dx���C�u�����̌㏈��
    DxLib_End();
}