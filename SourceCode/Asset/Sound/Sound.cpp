#include "Sound.h"
#include"../AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"

// コンストラクタ //

Sound::Sound()
    :soundType(-1)
    ,nowSoundTime(0.0f)
    ,attachedIndex(0)
{
}

// デストラクタ //

Sound::~Sound()
{
    for (auto tag : soundTagAll)
    {
        DeleteSoundMem(soundData[tag].soundHandle);
    }
}

// サウンド追加処理 //

void Sound::AddSound(string soundFileName, SoundTag tag, int volume,bool isDimension)
{
    SoundData sound = {};
    sound.volume = volume;
    sound.isDimension = isDimension;

    SetCreate3DSoundFlag(sound.isDimension);
    sound.soundHandle = AssetManager::GetSound(soundFileName.c_str());
    if (sound.soundHandle == -1)
    {
        return;
    }
    soundData.emplace(tag, sound);
}

void Sound::Update(VECTOR targetPos)
{
    ObjectBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    for (auto tag : soundTagAll)
    {
        auto& sound = soundData[tag];
        if (sound.isDimension&&IsPlaying(tag))
        {
            if (camera)
            {
                Set3DSoundListenerPosAndFrontPos_UpVecY(camera->GetPos(), camera->GetDir());
            }
            Set3DPositionSoundMem(targetPos, sound.soundHandle);
        }
    }
}

// 再生処理 //

void Sound::StartSound(SoundTag tag,int playType)
{
    auto& sound = soundData[tag];
    if (!CheckSoundMem(sound.soundHandle))
    {
        if (sound.isDimension)
        {
            Set3DPositionSoundMem(VGet(0.0f, 0.0f, 0.0f), sound.soundHandle);
            Set3DRadiusSoundMem(200.0f, sound.soundHandle);
        }
        ChangeVolumeSoundMem(sound.volume, sound.soundHandle);
        PlaySoundMem(sound.soundHandle, playType);
    }
}

void Sound::StartSoundOnce(SoundTag tag, int playType)
{
    auto& sound = soundData[tag];
    if (!CheckSoundMem(sound.soundHandle) && sound.soundOnce)
    {
        if (sound.isDimension)
        {
            Set3DPositionSoundMem(VGet(0.0f, 0.0f, 0.0f), sound.soundHandle);
            Set3DRadiusSoundMem(200.0f, sound.soundHandle);
        }
        ChangeVolumeSoundMem(sound.volume, sound.soundHandle);
        PlaySoundMem(sound.soundHandle, playType);
        sound.soundOnce = false;
    }
}

void Sound::StopSound(SoundTag tag)
{
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.soundHandle))
    {
        StopSoundMem(sound.soundHandle);
    }
}

void Sound::StopAllSound()
{
    for (auto& tag : soundTagAll)
    {
        StopSound(tag);
    }
}

bool Sound::IsPlaying(SoundTag tag)
{
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.soundHandle))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Sound::SoundData::SoundData()
    :soundHandle(-1)
    , volume(0)
    , isDimension(false)
    , soundOnce(true)
{
}