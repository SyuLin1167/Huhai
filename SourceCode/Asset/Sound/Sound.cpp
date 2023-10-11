#include "Sound.h"

#include"../AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Scene/PauseMenu/PauseMenu.h"

// コンストラクタ //

Sound::Sound()
    :soundType(-1)
    , nowSoundTime(0.0f)
    , attachedIndex(0)
    , prevSoundPos(VGet(0,0,0))
    , prevListnerPos(VGet(0,0,0))
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
}

// 追加処理 //

void Sound::AddSound(std::string fileName, SoundTag tag, bool isDim,bool volumeType)
{
    //サウンドデータ設定
    SoundData sound = {};
    sound.volumeType = volumeType;
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

// ドップラー効果 //

void Sound::Doppler(SoundTag tag, VECTOR pos)
{
    //3次元サウンドはカメラの距離に合わせて音量を変える
    ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
    auto& sound = soundData[tag];
    if (sound.isDim && IsPlaying(tag))
    {
        //サウンドに関わる座標設定
        if (camera)
        {
            Set3DPositionSoundMem(pos, sound.handle);
            Set3DSoundListenerPosAndFrontPos_UpVecY(camera->GetPos(), camera->GetPos() + camera->GetDir());

            //移動速度算出
            VECTOR soundVel = VScale(VSub(pos, prevSoundPos), 60.0f);
            Set3DVelocitySoundMem(soundVel, sound.handle);
            VECTOR listnerVel = VScale(VSub(camera->GetPos(), prevListnerPos), 60.0f);
            Set3DSoundListenerVelocity(listnerVel);

            //過去の座標に代入
            prevSoundPos = pos;
            prevListnerPos = camera->GetPos();
        };

    }
}

// 再生処理 //

void Sound::StartSound(SoundTag tag, int playType)
{
    //再生されていなかったらサウンド再生
    auto& sound = soundData[tag];
    if (!CheckSoundMem(sound.handle))
    {
        //サウンドの有効範囲設定
        if (sound.isDim)
        {
            Set3DRadiusSoundMem(500.0f, sound.handle);
        }

        if (sound.volumeType)
        {
            sound.volume = PauseMenu::Parameter("SE");
        }
        else
        {
            sound.volume = PauseMenu::Parameter("Bgm");
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
    if (sound.playOnce)
    {
        StartSound(tag, playType);
        sound.playOnce = false;
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
    , volume(150)
    , volumeType(false)
    , isDim(false)
    , playOnce(true)
{
}