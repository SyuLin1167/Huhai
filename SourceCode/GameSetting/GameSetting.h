#pragma once

/*GameSetting�N���X*/
class GameSetting
{
public:
    /// <summary>
    /// ����������
    /// </summary>
    static int Init();

    /// <summary>
    /// �㏈��
    /// </summary>
    static void Finalize();
private:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    GameSetting() {};

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameSetting() {};
	
    //���g�ւ̃C���X�^���X
    static GameSetting* gameSetting;
};

