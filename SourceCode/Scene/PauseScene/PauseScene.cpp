#include "PauseScene.h"
#include"PauseMenu/PauseMenu.h"

/// <summary>
/// コンストラクタ
/// </summary>
PauseScene::PauseScene()
    :SceneBase()
{
    //ゲーム画面保存
    bgHandle = LoadGraph("../Assets/BackGround/GameScene.png");

    PauseMenu::CreateInstance();
    PauseMenu::ResetTitleButton();
}

/// <summary>
/// デストラクタ
/// </summary>
PauseScene::~PauseScene()
{
    //処理なし
}

/// <summary>
/// ポーズメニュー初期化処理
/// </summary>
void PauseScene::InitPauesMenu()
{
    //ゲーム画面保存
    bgHandle = LoadGraph("../Assets/BackGround/GameScene.png");

    PauseMenu::ResetTitleButton();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
/// <returns>次のフレームのシーン</returns>
SceneBase* PauseScene::UpdateScene(const float deltaTime)
{
    PauseMenu::Update(deltaTime);
    return this;
}

/// <summary>
/// 描画処理
/// </summary>
void PauseScene::DrawScene()
{
    //ゲーム画面描画
    DrawGraph(bgX, bgY, bgHandle, FALSE);
    GraphFilter(bgHandle, DX_GRAPH_FILTER_GAUSS, PIXEL_WIDTH, GAUSS_PARAM);

    PauseMenu::Draw();
}