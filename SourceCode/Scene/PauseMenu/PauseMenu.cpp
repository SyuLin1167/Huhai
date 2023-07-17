#include "PauseMenu.h"

#include"../../UI/SetUp/Button/Button.h"
#include"../../UI/SetUp/TitleButton/TitleButton.h"
#include"../../Scene/TitleScene/Title.h"
#include"../../UI/SetUp/ParamButton/ParamButton.h"

//���Ԃւ̃|�C���^��`
PauseMenu* PauseMenu::pause = nullptr;

// �R���X�g���N�^ //

PauseMenu::PauseMenu()
{
    //�{�^���̒ǉ�
    AddButton("Camera");
    AddButton("Bloom");
    AddParam("Bgm", 150);
    AddParam("SE", 150);
    AddParam("Brightness", 60);
    paramData["Brightness"]->ParamMinMax(10, 95);
    AddParam("Sensitivity", 220);
    paramData["Sensitivity"]->ParamMinMax(60, 245);
}

// �f�X�g���N�^ //

PauseMenu::~PauseMenu()
{
}

// ���������� //

SceneBase* PauseMenu::Init()
{
    //�C���X�^���X����
    if (!pause)
    {
        pause = new PauseMenu;
    }

    //�Q�[����ʕۑ�
    pause->BgHandle = LoadGraph("../Assets/BackGround/GameScene.png");

    //�^�C�g���{�^���ǉ�
    delete pause->titleButton;
    pause->titleButton = new TitleButton(static_cast<int>(pause->paramData.size()) + 1);

    return pause;
}

// �㏈�� //

void PauseMenu::Finalize()
{
    //�C���X�^���X�폜
    if (pause)
    {
        delete pause;
    }
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

SceneBase* PauseMenu::Update(float deltaTime)
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

    return pause;
}

// �X�e�[�^�X��� //

bool PauseMenu::HasStatus(std::string name)
{
    if (pause)
    {
        return pause->buttonData[name]->GetButtonInput();
    }

    return false;
}

// �^�C�g���ړ� //

bool PauseMenu::BackToTitle()
{
    if (pause->titleButton)
    {
        return pause->titleButton->GetButtonInput();
    }

    return false;
}

// �^�C�g���{�^�����Z�b�g //

void PauseMenu::ResetTitleButton()
{
    pause->titleButton->ChangeToFalse();
}

// �p�����[�^�[�擾 //

int PauseMenu::Parameter(std::string name)
{
    if (pause)
    {
        return pause->paramData[name]->GetParam();
    }

    return -1;
}

// �`�揈�� //

void PauseMenu::Draw()
{
    //�Q�[����ʕ`��
    DrawGraph(BgX, BgY, pause->BgHandle, FALSE);
    GraphFilter(pause->BgHandle, DX_GRAPH_FILTER_GAUSS, 8, 1400);

    //�{�^���`��
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