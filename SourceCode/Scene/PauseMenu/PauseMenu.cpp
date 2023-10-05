#include "PauseMenu.h"

#include"../../UI/SetUp/Button/Button.h"
#include"../../UI/SetUp/TitleButton/TitleButton.h"
#include"../../Scene/TitleScene/TitleScene.h"
#include"../../UI/SetUp/ParamButton/ParamButton.h"

//実態へのポインタ定義
std::unique_ptr<PauseMenu> PauseMenu::pauseMenu = nullptr;

// コンストラクタ //

PauseMenu::PauseMenu()
{

    //フォントの読み込み
    ChangeFont("KillingFont", DX_CHARSET_DEFAULT);

    //ボタンの追加
    AddButton("Camera");
    AddButton("Bloom");
    AddParam("Bgm", 150);
    AddParam("SE", 150);
    AddParam("Brightness", 60);
    paramData["Brightness"]->ParamMinMax(10, 75);
    AddParam("Sensitivity", 220);
    paramData["Sensitivity"]->ParamMinMax(60, 245);

    //フォント設定
    AddFontResourceEx(".. /Assets/Font/KillingFont.otf", FR_PRIVATE, NULL);
}

// デストラクタ //

PauseMenu::~PauseMenu()
{
}

// 初期化処理 //

void PauseMenu::CreateInstance()
{
    //インスタンス生成
    if (!pauseMenu.get())
    {
        pauseMenu.reset(new PauseMenu);
    }
}

SceneBase* PauseMenu::GetPauseMenuInstance()
{
    //ゲーム画面保存
    pauseMenu->bgHandle = LoadGraph("../Assets/BackGround/GameScene.png");


    //タイトルボタン追加
    delete pauseMenu->titleButton;
    pauseMenu->titleButton = new TitleButton(static_cast<int>(pauseMenu->paramData.size() + 1));

    return pauseMenu.get();
}

// 後処理 //

void PauseMenu::Finalize()
{
}

// ボタン追加処理 //

void PauseMenu::AddButton(std::string name)
{
    auto iter = buttonData.find(name);
    if (iter == buttonData.end())
    {
        buttonData.emplace(name, new Button(name, static_cast<int>(buttonData.size())));
    }
}

// パラメーター追加処理 //

void PauseMenu::AddParam(std::string name,int value)
{
    auto iter = paramData.find(name);
    if (iter == paramData.end())
    {
        paramData.emplace(name, new ParamButton(name, static_cast<int>(paramData.size()), value));
    }
}

// 更新処理 //

SceneBase* PauseMenu::UpdateScene(float deltaTime)
{
    //ボタン更新
    for (auto& iter : buttonData)
    {
        iter.second->Update(deltaTime);
    }
    for (auto& iter : paramData)
    {
        iter.second->Update(deltaTime);
    }
    titleButton->Update(deltaTime);

    return pauseMenu.get();
}

// ステータス状態 //

bool PauseMenu::HasStatus(std::string name)
{
    if (pauseMenu)
    {
        return pauseMenu->buttonData[name]->GetButtonInput();
    }

    return false;
}

// タイトル移動 //

bool PauseMenu::BackToTitle()
{
    if (pauseMenu->titleButton)
    {
        return pauseMenu->titleButton->GetButtonInput();
    }

    return false;
}

// タイトルボタンリセット //

void PauseMenu::ResetTitleButton()
{
    pauseMenu->titleButton->ChangeToFalse();
}

// パラメーター取得 //

int PauseMenu::Parameter(std::string name)
{
    if (pauseMenu.get())
    {
        return pauseMenu->paramData[name]->GetParam();
    }

    return -1;
}

// 描画処理 //

void PauseMenu::DrawScene()
{
    //ゲーム画面描画
    DrawGraph(bgX, bgY, pauseMenu->bgHandle, FALSE);
    GraphFilter(pauseMenu->bgHandle, DX_GRAPH_FILTER_GAUSS, PIXEL_WIDTH, GAUSS_PARAM);

    //ボタン描画
    for (auto& iter : buttonData)
    {
        iter.second->Draw();
    }
    for (auto& iter : paramData)
    {
        iter.second->Draw();
    }
    pauseMenu->titleButton->Draw();
}