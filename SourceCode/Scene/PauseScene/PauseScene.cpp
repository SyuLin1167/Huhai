#include "PauseScene.h"
#include"PauseMenu/PauseMenu.h"

PauseScene::PauseScene()
    :SceneBase()
{
    //ゲーム画面保存
    bgHandle = LoadGraph(GAME_SCENE);

    PauseMenu::CreateInstance();
    PauseMenu::ResetTitleButton();
}

PauseScene::~PauseScene()
{
    //処理なし
}

void PauseScene::InitPauesMenu()
{
    //ゲーム画面保存
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
    //ゲーム画面描画
    DrawGraph(bgX, bgY, bgHandle, FALSE);
    GraphFilter(bgHandle, DX_GRAPH_FILTER_GAUSS, PIXEL_WIDTH, GAUSS_PARAM);

    PauseMenu::Draw();
}