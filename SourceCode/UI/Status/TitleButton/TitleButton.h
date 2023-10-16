#pragma once
#include<string>

#include"../Base/StatusBase.h"

/// <summary>
/// TitleButton�N���X
/// </summary>
class TitleButton :public StatusBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="num">:�{�^���ԍ�</param>
    TitleButton(int num);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~TitleButton();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// ���̓��Z�b�g
    /// </summary>
    void ChangeToFalse() { isInput = false; }
private:
    const float TITLE_BUTTON_POS_X = SCREEN_WIDTH * 0.41f;      //�{�^�����WX
    const float TITLE_BUTTON_POS_Y = SCREEN_HEIGHT / 9.0f;      //�{�^�����WY
    const int TITLE_BUTTON_WIDTH = 270;                         //�^�C�g���{�^����
    const int TITLE_BUTTON_HEIGHT = 45;                         //�^�C�g���{�^������

    class BlendMode* titleButtonBlend;                          //�u�����h���[�h
};

