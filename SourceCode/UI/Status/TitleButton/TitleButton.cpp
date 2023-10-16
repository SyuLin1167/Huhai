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
    objPos.x = TITLE_BUTTON_POS_X;
    objPos.y = TITLE_BUTTON_POS_Y * (num + 2);

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
/// <param name="deltaTime">:�f���^�^�C��</param>
void TitleButton::Update(const float deltaTime)
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

