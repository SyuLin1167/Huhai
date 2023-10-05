#include "PauseMenu.h"

#include"../../UI/SetUp/Button/Button.h"
#include"../../UI/SetUp/TitleButton/TitleButton.h"
#include"../../Scene/TitleScene/TitleScene.h"
#include"../../UI/SetUp/ParamButton/ParamButton.h"

//���Ԃւ̃|�C���^��`
std::unique_ptr<PauseMenu> PauseMenu::pauseMenu = nullptr;

// �R���X�g���N�^ //

PauseMenu::PauseMenu()
{

    //�t�H���g�̓ǂݍ���
    ChangeFont("KillingFont", DX_CHARSET_DEFAULT);

    //�{�^���̒ǉ�
    AddButton("Camera");
    AddButton("Bloom");
    AddParam("Bgm", 150);
    AddParam("SE", 150);
    AddParam("Brightness", 60);
    paramData["Brightness"]->ParamMinMax(10, 75);
    AddParam("Sensitivity", 220);
    paramData["Sensitivity"]->ParamMinMax(60, 245);

    //�t�H���g�ݒ�
    AddFontResourceEx(".. /Assets/Font/KillingFont.otf", FR_PRIVATE, NULL);
}

// �f�X�g���N�^ //

PauseMenu::~PauseMenu()
{
}

// ���������� //

void PauseMenu::CreateInstance()
{
    //�C���X�^���X����
    if (!pauseMenu.get())
    {
        pauseMenu.reset(new PauseMenu);
    }
}

SceneBase* PauseMenu::GetPauseMenuInstance()
{
    //�Q�[����ʕۑ�
    pauseMenu->bgHandle = LoadGraph("../Assets/BackGround/GameScene.png");


    //�^�C�g���{�^���ǉ�
    delete pauseMenu->titleButton;
    pauseMenu->titleButton = new TitleButton(static_cast<int>(pauseMenu->paramData.size() + 1));

    return pauseMenu.get();
}

// �㏈�� //

void PauseMenu::Finalize()
{
}

// �{�^���ǉ����� //

void PauseMenu::AddButton(std::string name)
{
    auto iter = buttonData.find(name);
    if (iter == buttonData.end())
    {
        buttonData.emplace(name, new Button(name, static_cast<int>(buttonData.size())));
    }
}

// �p�����[�^�[�ǉ����� //

void PauseMenu::AddParam(std::string name,int value)
{
    auto iter = paramData.find(name);
    if (iter == paramData.end())
    {
        paramData.emplace(name, new ParamButton(name, static_cast<int>(paramData.size()), value));
    }
}

// �X�V���� //

SceneBase* PauseMenu::UpdateScene(float deltaTime)
{
    //�{�^���X�V
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

// �X�e�[�^�X��� //

bool PauseMenu::HasStatus(std::string name)
{
    if (pauseMenu)
    {
        return pauseMenu->buttonData[name]->GetButtonInput();
    }

    return false;
}

// �^�C�g���ړ� //

bool PauseMenu::BackToTitle()
{
    if (pauseMenu->titleButton)
    {
        return pauseMenu->titleButton->GetButtonInput();
    }

    return false;
}

// �^�C�g���{�^�����Z�b�g //

void PauseMenu::ResetTitleButton()
{
    pauseMenu->titleButton->ChangeToFalse();
}

// �p�����[�^�[�擾 //

int PauseMenu::Parameter(std::string name)
{
    if (pauseMenu.get())
    {
        return pauseMenu->paramData[name]->GetParam();
    }

    return -1;
}

// �`�揈�� //

void PauseMenu::DrawScene()
{
    //�Q�[����ʕ`��
    DrawGraph(bgX, bgY, pauseMenu->bgHandle, FALSE);
    GraphFilter(pauseMenu->bgHandle, DX_GRAPH_FILTER_GAUSS, PIXEL_WIDTH, GAUSS_PARAM);

    //�{�^���`��
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