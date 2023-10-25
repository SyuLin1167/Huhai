#pragma once
#include<DxLib.h>
#include<unordered_map>
#include<string>

#include"SoundTag.h"

/// <summary>
/// �T�E���h�̊Ǘ�
/// </summary>
class Sound
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Sound();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Sound();

    /// <summary>
    /// �ǉ�����
    /// </summary>
    /// <param name="fileName">:�t�@�C����</param>
    /// <param name="tag">:�T�E���h�^�O</param>
    /// <param name="isDim">:���̎���(�f�t�H���g�E2����)</param>
    /// <param name="volumeType">:���ʃ^�C�v(�f�t�H���g�EBgm)</param>
    void AddSound(std::string fileName, SoundTag tag, bool isDim = false, bool volumeType = false);

    /// <summary>
    /// �h�b�v���[����
    /// </summary>
    /// <param name="tag">:�^�O</param>
    /// <param name="pos">:���W</param>
    void Doppler(SoundTag tag, VECTOR pos);

    /// <summary>
    /// �Đ�����
    /// </summary>
    /// <param name="tag">:�T�E���h�^�O</param>
    /// <param name="soundType">:�Đ��^�C�v</param>
    void StartSound(SoundTag tag, int playType);

    /// <summary>
    /// ��x�����Đ�����
    /// </summary>
    /// <param name="tag">:�T�E���h�^�O</param>
    /// <param name="playType">:�Đ��^�C�v</param>
    void StartSoundOnce(SoundTag tag, int playType);


    /// <summary>
    /// ��~����
    /// </summary>
    void StopSound(SoundTag tag);

    /// <summary>
    /// �S�T�E���h��~����
    /// </summary>
    void StopAllSound();

    /// <summary>
    /// �Đ����
    /// </summary>
    /// <returns>�Đ���:true|��~��:false</returns>
    bool IsPlaying(SoundTag tag);

    /// <summary>
    /// �T�E���h�f�[�^
    /// </summary>
    struct SoundData
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        SoundData();

        int handle;             //�T�E���h�n���h��
        int volume;             //����
        bool volumeType;        //���ʃ^�C�v
        bool isDim;             //����
        bool playOnce;          //�Đ���
    };

private:
    const int FIRST_VOLUME = 150;                           //��������
    const float RADIUS_SOUND = 500.0f;                      //�T�E���h�͈�

    int soundType;                                          //�T�E���hID
    int attachedIndex;                                      //�A�^�b�`��̃C���f�b�N�X
    
    float nowSoundTime;                                     //���݂̃T�E���h����

    VECTOR prevSoundPos;                                    //�ߋ��̃T�E���h���W
    VECTOR prevListnerPos;                                  //�ߋ��̃��X�i�[���W

    std::unordered_map<SoundTag, SoundData> soundData;      //�T�E���h�f�[�^
};

