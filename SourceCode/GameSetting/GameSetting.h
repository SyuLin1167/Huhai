#pragma once

//�J���[�r�b�g��
constexpr int ColorBit = 16;

constexpr auto SCREEN_WIDTH = 1920;       //�X�N���[����
constexpr auto SCREEN_HEIGHT = 1080;      //�X�N���[������

/*GameSetting�N���X*/
class GameSetting
{
public:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    GameSetting() {};

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameSetting() { Finalize(); }

    /// <summary>
    /// ����������
    /// </summary>
    int Init();

    /// <summary>
    /// �㏈��
    /// </summary>
    void Finalize();
};

