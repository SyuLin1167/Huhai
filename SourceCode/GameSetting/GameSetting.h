#pragma once


constexpr int ColorBit = 16;                                //�J���[�r�b�g��

constexpr int SCREEN_WIDTH = 1920;                          //�X�N���[����
constexpr int SCREEN_HEIGHT = 1080;                         //�X�N���[������
constexpr int SCREEN_CENTER_WIDTH = SCREEN_WIDTH / 2;       //�X�N���[�����S��
constexpr int SCREEN_CENTER_HEIGHT = SCREEN_HEIGHT / 2;     //�X�N���[�����S����

/// <summary>
/// GameSetting�N���X
/// </summary>
class GameSetting
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameSetting();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameSetting();

    /// <summary>
    /// ����������
    /// </summary>
    /// <returns>�������ł������ǂ���</returns>
    int Init();
};

