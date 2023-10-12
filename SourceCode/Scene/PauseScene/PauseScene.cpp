#include "PauseScene.h"
#include"PauseMenu/PauseMenu.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PauseScene::PauseScene()
    :SceneBase()
{
    //�Q�[����ʕۑ�
    bgHandle = LoadGraph("../Assets/BackGround/GameScene.png");

    PauseMenu::CreateInstance();
    PauseMenu::ResetTitleButton();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PauseScene::~PauseScene()
{
    //�����Ȃ�
}

/// <summary>
/// �|�[�Y���j���[����������
/// </summary>
void PauseScene::InitPauesMenu()
{
    //�Q�[����ʕۑ�
    bgHandle = LoadGraph("../Assets/BackGround/GameScene.png");

    PauseMenu::ResetTitleButton();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
/// <returns>���̃t���[���̃V�[��</returns>
SceneBase* PauseScene::UpdateScene(const float deltaTime)
{
    PauseMenu::Update(deltaTime);
    return this;
}

/// <summary>
/// �`�揈��
/// </summary>
void PauseScene::DrawScene()
{
    //�Q�[����ʕ`��
    DrawGraph(bgX, bgY, bgHandle, FALSE);
    GraphFilter(bgHandle, DX_GRAPH_FILTER_GAUSS, PIXEL_WIDTH, GAUSS_PARAM);

    PauseMenu::Draw();
}