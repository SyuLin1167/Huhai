#pragma once
#include<string>

#include"../../../GameSetting/GameSetting.h"
#include"../../UIBase/UIBase.h"

constexpr auto killingFont = "KillingFont";    //�t�H���g��
constexpr auto msGothic = "�l�r�@�S�V�b�N";    //�t�H���g��

/// <summary>
/// StatusBase�N���X
/// </summary>
class StatusBase :public UIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name">:�{�^����</param>
    StatusBase(std::string name);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~StatusBase();

    /// <summary>
    /// ���͏���
    /// </summary>
    void ProcessInput();

    /// <summary>
    /// ������̍��W�w��`�揈��
    /// </summary>
    /// <param name="x">:���WX</param>
    /// <param name="y">:���WY</param>
    void DrawStr(int x, int y);

    /// <summary>
    /// �{�^���̍��W�w��`�揈��
    /// </summary>
    /// <param name="x">:���WX</param>
    /// <param name="y">:���WY</param>
    void DrawButton(int x, int y);

protected:
    std::string buttonName;     //�{�^����
    int buttonWidth;            //�{�^����
    int buttonHeight;           //�{�^������

    const int FONT_SIZE = 45;   //�t�H���g�T�C�Y

    const int StrSpace = 300;   //�{�^���Ƃ̊Ԋu

    const int whiteColor;       //���F
};