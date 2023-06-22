#include "Sound.h"

#include"../AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"

// �R���X�g���N�^ //

Sound::Sound()
    :soundType(-1)
    , nowSoundTime(0.0f)
    , attachedIndex(0)
{
}

// �f�X�g���N�^ //

Sound::~Sound()
{
    //�T�E���h�폜
    for (auto tag : soundTagAll)
    {
        DeleteSoundMem(soundData[tag].handle);
    }

    //�f�[�^�폜

}

// �ǉ����� //

void Sound::AddSound(std::string fileName, SoundTag tag, int volume, bool isDim)
{
    //�T�E���h�f�[�^�ݒ�
    SoundData sound = {};
    sound.volume = volume;
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

// �X�V���� //

void Sound::Update(VECTOR targetPos)
{
    //3�����T�E���h�̓J�����̋����ɍ��킹�ĉ��ʂ�ς���
    ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    for (auto tag : soundTagAll)
    {
        auto& sound = soundData[tag];
        if (sound.isDim && IsPlaying(tag))
        {
            if (camera)
            {
                Set3DSoundListenerPosAndFrontPos_UpVecY(camera->GetPos(), camera->GetDir());
            }
            Set3DPositionSoundMem(targetPos, sound.handle);
        }
    }
}

// �Đ����� //

void Sound::StartSound(SoundTag tag, int playType)
{
    //�Đ�����Ă��Ȃ�������T�E���h�Đ�
    auto& sound = soundData[tag];
    if (!CheckSoundMem(sound.handle))
    {
        if (sound.isDim)
        {
            Set3DPositionSoundMem(VGet(0.0f, 0.0f, 0.0f), sound.handle);
            Set3DRadiusSoundMem(200.0f, sound.handle);
        }
        ChangeVolumeSoundMem(sound.volume, sound.handle);
        PlaySoundMem(sound.handle, playType);
    }
}

// ��x�����Đ����� //

void Sound::StartSoundOnce(SoundTag tag, int playType)
{
    //�Đ�����Ă��Ȃ�������T�E���h�Đ�
    auto& sound = soundData[tag];
    if (!sound.playOnce)
    {
        if (!CheckSoundMem(sound.handle))
        {
            if (sound.isDim)
            {
                Set3DPositionSoundMem(VGet(0.0f, 0.0f, 0.0f), sound.handle);
                Set3DRadiusSoundMem(200.0f, sound.handle);
            }
            ChangeVolumeSoundMem(sound.volume, sound.handle);
            PlaySoundMem(sound.handle, playType);
            sound.playOnce = true;
        }
    }
}

// ��~���� //

void Sound::StopSound(SoundTag tag)
{
    //�T�E���h���Đ�����Ă������~
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.handle))
    {
        StopSoundMem(sound.handle);
    }
}

// �S�T�E���h��~���� //

void Sound::StopAllSound()
{
    //���ׂẴT�E���h�ɒ�~����������
    for (auto& tag : soundTagAll)
    {
        StopSound(tag);
    }
}

// �Đ���� //

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

// �R���X�g���N�^ //

Sound::SoundData::SoundData()
    :handle(-1)
    , volume(0)
    , isDim(false)
    , playOnce(false)
{
}