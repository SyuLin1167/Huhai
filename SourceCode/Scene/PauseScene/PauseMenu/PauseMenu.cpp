#include "PauseMenu.h"

#include"../../../UI/Status/Button/Button.h"
#include"../../../UI/Status/TitleButton/TitleButton.h"
#include"../../../Scene/TitleScene/TitleScene.h"
#include"../../../UI/Status/ParamButton/ParamButton.h"

//���Ԃւ̃|�C���^��`
std::unique_ptr<PauseMenu> PauseMenu::singleton = nullptr;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PauseMenu::PauseMenu()
{
    //�t�H���g�̓ǂݍ���
    ChangeFont(killingFont, DX_CHARSET_DEFAULT);

    //�{�^���̒ǉ�
    ButtonName buttonName;
    AddButton(buttonName.camera);
    AddButton(buttonName.bloom);
    AddParam(buttonName.bgm, FIRST_SOUND_PARAM);
    AddParam(buttonName.se, FIRST_SOUND_PARAM);
    AddParam(buttonName.bright, FIRST_BRIGHT_PARAM);
    paramData[buttonName.bright]->ParamMinMax(MIN_BRIGHT_PARAM, MAX_BRIGHT_PARAM);
    AddParam(buttonName.sensi, FIRST_SENSITIVITY);
    paramData[buttonName.sensi]->ParamMinMax(MIN_SENSITIVITY, MAX_SENSITIVITY);

    //�t�H���g�ݒ�
    AddFontResourceEx("../Assets/Font/KillingFont.otf", FR_PRIVATE, NULL);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PauseMenu::~PauseMenu()
{
    //�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void PauseMenu::CreateInstance()
{
    //�C���X�^���X����
    if (!singleton.get())
    {
        singleton.reset(new PauseMenu);
    }
}

/// <summary>
/// �{�^���ǉ�����
/// </summary>
/// <param name="name">:�o�^��</param>
void PauseMenu::AddButton(std::string name)
{
    auto iter = buttonData.find(name);
    if (iter == buttonData.end())
    {
        buttonData.emplace(name, new Button(name, static_cast<int>(buttonData.size())));
    }
}

/// <summary>
/// �p�����[�^�[�ǉ�����
/// </summary>
/// <param name="name">:�o�^��</param>
/// <param name="value">:�p�����[�^�[�����l</param>
void PauseMenu::AddParam(std::string name,int value)
{
    auto iter = paramData.find(name);
    if (iter == paramData.end())
    {
        paramData.emplace(name, new ParamButton(name, static_cast<int>(paramData.size()), value));
    }
}

/// <summary>
/// �X�V����
/// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
void PauseMenu::Update(const float deltaTime)
{
    //�{�^���X�V
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

/// <summary>
/// �X�e�[�^�X���
/// </summary>
/// <param name="name">:�{�^����</param>
/// <returns>�I��:true|�I�t:false</returns>
bool PauseMenu::HasStatus(std::string name)
{
    if (singleton)
    {
        return singleton->buttonData[name]->GetButtonInput();
    }

    return false;
}

/// <summary>
/// �^�C�g���ړ�
/// </summary>
/// <returns>�ړ�����:true|���Ȃ�:false</returns>
bool PauseMenu::BackToTitle()
{
    if (singleton->titleButton)
    {
        return singleton->titleButton->GetButtonInput();
    }

    return false;
}

/// <summary>
/// �^�C�g���{�^�����Z�b�g
/// </summary>
void PauseMenu::ResetTitleButton()
{
    //�^�C�g���{�^���ǉ�
    delete singleton->titleButton;
    singleton->titleButton = new TitleButton(static_cast<int>(singleton->paramData.size() + 1));

    //�^�C�g���{�^���ǉ�
    delete singleton->titleButton;
    singleton->titleButton = new TitleButton(static_cast<int>(singleton->paramData.size() + 1));
    singleton->titleButton->ChangeToFalse();
}

/// <summary>
/// �p�����[�^�[�擾
/// </summary>
/// <param name="name">:�p�����[�^�[��</param>
/// <returns>:�p�����[�^�[</returns>
int PauseMenu::Parameter(std::string name)
{
    if (singleton.get())
    {
        return singleton->paramData[name]->GetParam();
    }

    return -1;
}

/// <summary>
/// �`�揈��
/// </summary>
void PauseMenu::Draw()
{
    //�{�^���`��
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

