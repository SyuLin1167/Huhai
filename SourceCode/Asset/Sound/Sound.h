#pragma once
#include<DxLib.h>
#include<unordered_map>
#include<string>

#include"SoundTag.h"
using namespace std;

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
    /// <param name="soundFileName">:�T�E���h�t�@�C����</param>
    void AddSound(string soundFileName, SoundTag tag, int volume,bool isDimension=false);

    void Update(VECTOR targetPos);

    /// <summary>
    /// �Đ�����
    /// </summary>
    /// <param name="soundType">:�T�E���h�^�C�v</param>
    void StartSound(SoundTag tag, int playType);
    void StartSoundOnce(SoundTag tag, int playType);


    /// <summary>
    /// ��~����
    /// </summary>
    void StopSound(SoundTag tag);
    void StopAllSound();

    /// <summary>
    /// �Đ������ǂ���
    /// </summary>
    /// <returns>�Đ����</returns>
    bool IsPlaying(SoundTag tag);

    struct SoundData
    {
    public:
        /// <summary>
        /// SoundData�R���X�g���N�^
        /// </summary>
        SoundData();

        int soundHandle;        //�T�E���h�n���h��
        int volume;
        bool isDimension;
        bool soundOnce;
    };

private:
    unordered_map<SoundTag, SoundData> soundData;
    int soundType;              //�T�E���hID
    int attachedIndex;          //�A�^�b�`��̃C���f�b�N�X
    float nowSoundTime;          //���݂̃T�E���h����
};

