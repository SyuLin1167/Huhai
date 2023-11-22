#include "PauseScene.h"
#include"PauseMenu/PauseMenu.h"

PauseScene::PauseScene()
    :SceneBase()
{
    //�Q�[����ʕۑ�
    bgHandle = LoadGraph(GAME_SCENE);

    PauseMenu::CreateInstance();
    PauseMenu::ResetTitleButton();
}

PauseScene::~PauseScene()
{
    //�����Ȃ�
}

void PauseScene::InitPauesMenu()
{
    //�Q�[����ʕۑ�
    bgHandle = LoadGraph("../Assets/BackGround/GameScene.png");

    PauseMenu::ResetTitleButton();
}

SceneBase* PauseScene::UpdateScene(const float deltaTime)
{
    PauseMenu::Update(deltaTime);
    return this;
}

void PauseScene::DrawScene()
{
    //�Q�[����ʕ`��
    DrawGraph(bgX, bgY, bgHandle, FALSE);
    GraphFilter(bgHandle, DX_GRAPH_FILTER_GAUSS, PIXEL_WIDTH, GAUSS_PARAM);

    PauseMenu::Draw();
}