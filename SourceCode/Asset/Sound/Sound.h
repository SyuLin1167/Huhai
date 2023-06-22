#pragma once

#include<DxLib.h>
#include<unordered_map>
#include<string>

#include"SoundTag.h"

/*Sound�N���X*/
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
    /// <param name="volume">:����</param>
    /// <param name="isDim">:���̎���(�f�t�H���g�E2����)</param>
    void AddSound(std::string fileName, SoundTag tag, int volume, bool isDim = false);

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="pos"></param>
    void Update(VECTOR pos);

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
    /// �T�E���h����̃f�[�^�\����
    /// </summary>
    struct SoundData
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        SoundData();

        int handle;        //�T�E���h�n���h��
        int volume;             //����
        bool isDim;             //����
        bool playOnce;         //�Đ���
    };

private:
    int soundType;                                          //�T�E���hID
    int attachedIndex;                                      //�A�^�b�`��̃C���f�b�N�X
    
    float nowSoundTime;                                     //���݂̃T�E���h����

    std::unordered_map<SoundTag, SoundData> soundData;      //�T�E���h�f�[�^
};

