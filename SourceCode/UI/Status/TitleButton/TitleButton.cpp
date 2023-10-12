#include "TitleButton.h"

#include"../../../GameSetting/GameSetting.h"
#include"../../../BlendMode/BlendMode.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="num">:�{�^���ԍ�</param>
TitleButton::TitleButton(int num)
    :StatusBase("BackToTitle")
{
    //�{�^���ݒ�
    buttonWidth = TITLE_BUTTON_WIDTH;
    buttonHeight = TITLE_BUTTON_HEIGHT;
    objPos.x = static_cast<float>(SCREEN_WIDTH) * (2.5f / 6.0f);
    objPos.y = static_cast<float>(SCREEN_HEIGHT) * (num + 2) / 9.0f;

    titleButtonBlend = new BlendMode;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleButton::~TitleButton()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
void TitleButton::Update(float deltaTime)
{
    ProcessInput();
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleButton::Draw()
{
    SetFontSize(45);
    //�{�^���`��
    if (hasMauseClick)
    {
        titleButtonBlend->Darken();
    }
    DrawStr(static_cast<int>(objPos.x), static_cast<int>(objPos.y));

    titleButtonBlend->NoBlend();
}

