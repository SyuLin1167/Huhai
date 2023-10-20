#include "Sound.h"

#include"../AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Scene/PauseScene/PauseMenu/PauseMenu.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Sound::Sound()
    :soundType(-1)
    , nowSoundTime(0.0f)
    , attachedIndex(0)
    , prevSoundPos(VGet(0,0,0))
    , prevListnerPos(VGet(0,0,0))
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Sound::~Sound()
{
    //�T�E���h�폜
    for (auto tag : soundTagAll)
    {
        DeleteSoundMem(soundData[tag].handle);
    }
}

/// <summary>
/// �ǉ�����
/// </summary>
/// <param name="fileName">:�t�@�C����</param>
/// <param name="tag">:�T�E���h�^�O</param>
/// <param name="isDim">:���̎���(�f�t�H���g�E2����)</param>
/// <param name="volumeType">:���ʃ^�C�v(�f�t�H���g�EBgm)</param>
void Sound::AddSound(std::string fileName, SoundTag tag, bool isDim,bool volumeType)
{
    //�T�E���h�f�[�^�ݒ�
    SoundData sound = {};
    sound.volumeType = volumeType;
    sound.volume = FIRST_VOLUME;
    sound.isDim = isDim;

    //�T�E���h�o�^&�擾
    SetCreate3DSoundFlag(sound.isDim);
    sound.handle = AssetManager::GetSound(fileName.c_str());

    //���g���󂾂����炻�̂܂ܕԂ�
    if (sound.handle == -1)
    {
        return ;
    }

    //�f�[�^�ǉ�
    soundData.emplace(tag, sound);
}

/// <summary>
/// �h�b�v���[����
/// </summary>
/// <param name="tag">:�^�O</param>
/// <param name="pos">:���W</param>
void Sound::Doppler(SoundTag tag, VECTOR pos)
{
    //3�����T�E���h�̓J�����̋����ɍ��킹�ĉ��ʂ�ς���
    ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
    auto& sound = soundData[tag];
    if (sound.isDim && IsPlaying(tag))
    {
        //�T�E���h�Ɋւ����W�ݒ�
        if (camera)
        {
            Set3DPositionSoundMem(pos, sound.handle);
            Set3DSoundListenerPosAndFrontPos_UpVecY(camera->GetPos(), camera->GetPos() + camera->GetDir());

            //�ړ����x�Z�o
            const float SCALE = 60.0f;
            VECTOR soundVel = VScale(VSub(pos, prevSoundPos), SCALE);
            Set3DVelocitySoundMem(soundVel, sound.handle);
            VECTOR listnerVel = VScale(VSub(camera->GetPos(), prevListnerPos), SCALE);
            Set3DSoundListenerVelocity(listnerVel);

            //�ߋ��̍��W�ɑ��
            prevSoundPos = pos;
            prevListnerPos = camera->GetPos();
        };

    }
}

/// <summary>
/// �Đ�����
/// </summary>
/// <param name="tag">:�T�E���h�^�O</param>
/// <param name="soundType">:�Đ��^�C�v</param>
void Sound::StartSound(SoundTag tag, int playType)
{
    //�Đ�����Ă��Ȃ�������T�E���h�Đ�
    auto& sound = soundData[tag];
    if (!CheckSoundMem(sound.handle))
    {
        //�T�E���h�̗L���͈͐ݒ�
        if (sound.isDim)
        {
            Set3DRadiusSoundMem(RADIUS_SOUND, sound.handle);
        }

        ButtonName buttonName;
        if (sound.volumeType)
        {
            sound.volume = PauseMenu::Parameter(buttonName.se);
        }
        else
        {
            sound.volume = PauseMenu::Parameter(buttonName.bgm);
        }

        ChangeVolumeSoundMem(sound.volume, sound.handle);

        PlaySoundMem(sound.handle, playType);
    }
}

/// <summary>
/// ��x�����Đ�����
/// </summary>
/// <param name="tag">:�T�E���h�^�O</param>
/// <param name="playType">:�Đ��^�C�v</param>
void Sound::StartSoundOnce(SoundTag tag, int playType)
{
    //�Đ�����Ă��Ȃ�������T�E���h�Đ�
    auto& sound = soundData[tag];
    if (sound.playOnce)
    {
        StartSound(tag, playType);
        sound.playOnce = false;
    }
}

/// <summary>
/// ��~����
/// </summary>
void Sound::StopSound(SoundTag tag)
{
    //�T�E���h���Đ�����Ă������~
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.handle))
    {
        StopSoundMem(sound.handle);
    }
}

/// <summary>
/// �S�T�E���h��~����
/// </summary>
void Sound::StopAllSound()
{
    //���ׂẴT�E���h�ɒ�~����������
    for (auto& tag : soundTagAll)
    {
        StopSound(tag);
    }
}

/// <summary>
/// �Đ����
/// </summary>
/// <returns>�Đ���:true|��~��:false</returns>
bool Sound::IsPlaying(SoundTag tag)
{
    //�Đ�����Ă�����Đ����ɂ���
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.handle))
    {
        return true;
    }
    else
    {
        //����Ă��Ȃ��������~���ɂ���
        return false;
    }
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Sound::SoundData::SoundData()
    :handle(-1)
    , volume()
    , volumeType(false)
    , isDim(false)
    , playOnce(true)
{
}