#include "Sound.h"

#include"../AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"

// コンストラクタ //

Sound::Sound()
    :soundType(-1)
    , nowSoundTime(0.0f)
    , attachedIndex(0)
{
}

// デストラクタ //

Sound::~Sound()
{
    //サウンド削除
    for (auto tag : soundTagAll)
    {
        DeleteSoundMem(soundData[tag].handle);
    }

    //データ削除

}

// 追加処理 //

void Sound::AddSound(std::string fileName, SoundTag tag, int volume, bool isDim)
{
    //サウンドデータ設定
    SoundData sound = {};
    sound.volume = volume;
    sound.isDim = isDim;

    //サウンド登録&取得
    SetCreate3DSoundFlag(sound.isDim);
    sound.handle = AssetManager::GetSound(fileName.c_str());

    //中身が空だったらそのまま返す
    if (sound.handle == -1)
    {
        return ;
    }

    //データ追加
    soundData.emplace(tag, sound);
}

// 更新処理 //

void Sound::Update(VECTOR targetPos)
{
    //3次元サウンドはカメラの距離に合わせて音量を変える
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

// 再生処理 //

void Sound::StartSound(SoundTag tag, int playType)
{
    //再生されていなかったらサウンド再生
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

// 一度だけ再生処理 //

void Sound::StartSoundOnce(SoundTag tag, int playType)
{
    //再生されていなかったらサウンド再生
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

// 停止処理 //

void Sound::StopSound(SoundTag tag)
{
    //サウンドが再生されていたら停止
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.handle))
    {
        StopSoundMem(sound.handle);
    }
}

// 全サウンド停止処理 //

void Sound::StopAllSound()
{
    //すべてのサウンドに停止処理をする
    for (auto& tag : soundTagAll)
    {
        StopSound(tag);
    }
}

// 再生状態 //

bool Sound::IsPlaying(SoundTag tag)
{
    //再生されていたら再生中にする
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.handle))
    {
        return true;
    }
    else
    {
        //されていなかったら停止中にする
        return false;
    }
}

// コンストラクタ //

Sound::SoundData::SoundData()
    :handle(-1)
    , volume(0)
    , isDim(false)
    , playOnce(false)
{
}