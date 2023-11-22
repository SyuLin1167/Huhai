#include "PauseScene.h"
#include"PauseMenu/PauseMenu.h"

PauseScene::PauseScene()
    :SceneBase()
{
    //ƒQ[ƒ€‰æ–Ê•Û‘¶
    bgHandle = LoadGraph(GAME_SCENE);

    PauseMenu::CreateInstance();
    PauseMenu::ResetTitleButton();
}

PauseScene::~PauseScene()
{
    //ˆ—‚È‚µ
}

void PauseScene::InitPauesMenu()
{
    //ƒQ[ƒ€‰æ–Ê•Û‘¶
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
    //ƒQ[ƒ€‰æ–Ê•`‰æ
    DrawGraph(bgX, bgY, bgHandle, FALSE);
    GraphFilter(bgHandle, DX_GRAPH_FILTER_GAUSS, PIXEL_WIDTH, GAUSS_PARAM);

    PauseMenu::Draw();
}