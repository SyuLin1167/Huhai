#include "PauseMenu.h"

#include"../../UI/SetUp/Button/Button.h"
#include"../../UI/SetUp/TitleButton/TitleButton.h"
#include"../../Scene/TitleScene/Title.h"
#include"../../UI/SetUp/ParamButton/ParamButton.h"

//実態へのポインタ定義
PauseMenu* PauseMenu::pause = nullptr;

// コンストラクタ //

PauseMenu::PauseMenu()
{
    //ボタンの追加
    AddButton("Camera");
    AddButton("Bloom");
    AddParam("Bgm", 150);
    AddParam("SE", 150);
    AddParam("Brightness", 60);
    paramData["Brightness"]->ParamMinMax(10, 95);
    AddParam("Sensitivity", 220);
    paramData["Sensitivity"]->ParamMinMax(60, 245);
}

// デストラクタ //

PauseMenu::~PauseMenu()
{
}

// 初期化処理 //

SceneBase* PauseMenu::Init()
{
    //インスタンス生成
    if (!pause)
    {
        pause = new PauseMenu;
    }

    //ゲーム画面保存
    pause->BgHandle = LoadGraph("../Assets/BackGround/GameScene.png");

    //タイトルボタン追加
    delete pause->titleButton;
    pause->titleButton = new TitleButton(static_cast<int>(pause->paramData.size()) + 1);

    return pause;
}

// 後処理 //

void PauseMenu::Finalize()
{
    //インスタンス削除
    if (pause)
    {
        delete pause;
    }
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

SceneBase* PauseMenu::Update(float deltaTime)
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

    return pause;
}

// ステータス状態 //

bool PauseMenu::HasStatus(std::string name)
{
    if (pause)
    {
        return pause->buttonData[name]->GetButtonInput();
    }

    return false;
}

// タイトル移動 //

bool PauseMenu::BackToTitle()
{
    if (pause->titleButton)
    {
        return pause->titleButton->GetButtonInput();
    }

    return false;
}

// タイトルボタンリセット //

void PauseMenu::ResetTitleButton()
{
    pause->titleButton->ChangeToFalse();
}

// パラメーター取得 //

int PauseMenu::Parameter(std::string name)
{
    if (pause)
    {
        return pause->paramData[name]->GetParam();
    }

    return -1;
}

// 描画処理 //

void PauseMenu::Draw()
{
    //ゲーム画面描画
    DrawGraph(BgX, BgY, pause->BgHandle, FALSE);
    GraphFilter(pause->BgHandle, DX_GRAPH_FILTER_GAUSS, 8, 1400);

    //ボタン描画
    for (auto& iter : buttonData)
    {
        iter.second->Draw();
    }
    for (auto& iter : paramData)
    {
        iter.second->Draw();
    }
    titleButton->Draw();
}