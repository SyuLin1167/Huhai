#include "PauseMenu.h"

#include"../../../UI/Status/Button/Button.h"
#include"../../../UI/Status/TitleButton/TitleButton.h"
#include"../../../Scene/TitleScene/TitleScene.h"
#include"../../../UI/Status/ParamButton/ParamButton.h"

//実態へのポインタ定義
std::unique_ptr<PauseMenu> PauseMenu::pauseMenu = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
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

/// <summary>
/// デストラクタ
/// </summary>
PauseMenu::~PauseMenu()
{
    //処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void PauseMenu::CreateInstance()
{
    //インスタンス生成
    if (!pauseMenu.get())
    {
        pauseMenu.reset(new PauseMenu);
    }
}

/// <summary>
/// ボタン追加処理
/// </summary>
/// <param name="name">:登録名</param>
void PauseMenu::AddButton(std::string name)
{
    auto iter = buttonData.find(name);
    if (iter == buttonData.end())
    {
        buttonData.emplace(name, new Button(name, static_cast<int>(buttonData.size())));
    }
}

/// <summary>
/// パラメーター追加処理
/// </summary>
/// <param name="name">:登録名</param>
/// <param name="value">:パラメーター初期値</param>
void PauseMenu::AddParam(std::string name,int value)
{
    auto iter = paramData.find(name);
    if (iter == paramData.end())
    {
        paramData.emplace(name, new ParamButton(name, static_cast<int>(paramData.size()), value));
    }
}

/// <summary>
/// 更新処理
/// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
void PauseMenu::Update(float deltaTime)
{
    //ボタン更新
    for (auto& iter : pauseMenu->buttonData)
    {
        iter.second->Update(deltaTime);
    }
    for (auto& iter : pauseMenu->paramData)
    {
        iter.second->Update(deltaTime);
    }
    pauseMenu->titleButton->Update(deltaTime);
}

/// <summary>
/// ステータス状態
/// </summary>
/// <param name="name">:ボタン名</param>
/// <returns>オン:true|オフ:false</returns>
bool PauseMenu::HasStatus(std::string name)
{
    if (pauseMenu)
    {
        return pauseMenu->buttonData[name]->GetButtonInput();
    }

    return false;
}

/// <summary>
/// タイトル移動
/// </summary>
/// <returns>移動する:true|しない:false</returns>
bool PauseMenu::BackToTitle()
{
    if (pauseMenu->titleButton)
    {
        return pauseMenu->titleButton->GetButtonInput();
    }

    return false;
}

/// <summary>
/// タイトルボタンリセット
/// </summary>
void PauseMenu::ResetTitleButton()
{
    //タイトルボタン追加
    delete pauseMenu->titleButton;
    pauseMenu->titleButton = new TitleButton(static_cast<int>(pauseMenu->paramData.size() + 1));

    //タイトルボタン追加
    delete pauseMenu->titleButton;
    pauseMenu->titleButton = new TitleButton(static_cast<int>(pauseMenu->paramData.size() + 1));
    pauseMenu->titleButton->ChangeToFalse();
}

/// <summary>
/// パラメーター取得
/// </summary>
/// <param name="name">:パラメーター名</param>
/// <returns>:パラメーター</returns>
int PauseMenu::Parameter(std::string name)
{
    if (pauseMenu.get())
    {
        return pauseMenu->paramData[name]->GetParam();
    }

    return -1;
}

/// <summary>
/// 描画処理
/// </summary>
void PauseMenu::Draw()
{
    //ボタン描画
    for (auto& iter : pauseMenu->buttonData)
    {
        iter.second->Draw();
    }
    for (auto& iter : pauseMenu->paramData)
    {
        iter.second->Draw();
    }
    pauseMenu->titleButton->Draw();
}