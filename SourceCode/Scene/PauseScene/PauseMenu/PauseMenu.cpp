#include "PauseMenu.h"

#include"../../../UI/Status/Button/Button.h"
#include"../../../UI/Status/TitleButton/TitleButton.h"
#include"../../../Scene/TitleScene/TitleScene.h"
#include"../../../UI/Status/ParamButton/ParamButton.h"

std::unique_ptr<PauseMenu> PauseMenu::singleton = nullptr;

PauseMenu::PauseMenu()
{
    //フォントの読み込み
    ChangeFont(killingFont, DX_CHARSET_DEFAULT);

    //ボタンの追加
    ButtonName buttonName;
    AddButton(buttonName.camera);
    AddButton(buttonName.bloom);
    AddParam(buttonName.bgm, FIRST_SOUND_PARAM);
    AddParam(buttonName.se, FIRST_SOUND_PARAM);
    AddParam(buttonName.bright, FIRST_BRIGHT_PARAM);
    paramData[buttonName.bright]->ParamMinMax(MIN_BRIGHT_PARAM, MAX_BRIGHT_PARAM);
    AddParam(buttonName.sensi, FIRST_SENSITIVITY);
    paramData[buttonName.sensi]->ParamMinMax(MIN_SENSITIVITY, MAX_SENSITIVITY);

    //フォント設定
    AddFontResourceEx("../Assets/Font/KillingFont.otf", FR_PRIVATE, NULL);
}

PauseMenu::~PauseMenu()
{
    //処理なし
}

void PauseMenu::CreateInstance()
{
    //インスタンス生成
    if (!singleton.get())
    {
        singleton.reset(new PauseMenu);
    }
}

void PauseMenu::AddButton(std::string name)
{
    auto iter = buttonData.find(name);
    if (iter == buttonData.end())
    {
        buttonData.emplace(name, new Button(name, static_cast<int>(buttonData.size())));
    }
}

void PauseMenu::AddParam(std::string name,int value)
{
    auto iter = paramData.find(name);
    if (iter == paramData.end())
    {
        paramData.emplace(name, new ParamButton(name, static_cast<int>(paramData.size()), value));
    }
}

void PauseMenu::Update(const float deltaTime)
{
    //ボタン更新
    for (auto& iter : singleton->buttonData)
    {
        iter.second->Update(deltaTime);
    }
    for (auto& iter : singleton->paramData)
    {
        iter.second->Update(deltaTime);
    }
    singleton->titleButton->Update(deltaTime);
}

bool PauseMenu::HasStatus(std::string name)
{
    if (singleton)
    {
        return singleton->buttonData[name]->GetButtonInput();
    }

    return false;
}

bool PauseMenu::BackToTitle()
{
    if (singleton->titleButton)
    {
        return singleton->titleButton->GetButtonInput();
    }

    return false;
}

void PauseMenu::ResetTitleButton()
{
    //タイトルボタン追加
    delete singleton->titleButton;
    singleton->titleButton = new TitleButton(static_cast<int>(singleton->paramData.size() + 1));

    //タイトルボタン追加
    delete singleton->titleButton;
    singleton->titleButton = new TitleButton(static_cast<int>(singleton->paramData.size() + 1));
    singleton->titleButton->ChangeToFalse();
}

int PauseMenu::Parameter(std::string name)
{
    if (singleton.get())
    {
        return singleton->paramData[name]->GetParam();
    }

    return -1;
}

void PauseMenu::Draw()
{
    //ボタン描画
    for (auto& iter : singleton->buttonData)
    {
        iter.second->Draw();
    }
    for (auto& iter : singleton->paramData)
    {
        iter.second->Draw();
    }
    singleton->titleButton->Draw();
}

