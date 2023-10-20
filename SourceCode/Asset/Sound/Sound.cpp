#include "Sound.h"

#include"../AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Scene/PauseScene/PauseMenu/PauseMenu.h"

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
Sound::~Sound()
{
    //サウンド削除
    for (auto tag : soundTagAll)
    {
        DeleteSoundMem(soundData[tag].handle);
    }
}

/// <summary>
/// 追加処理
/// </summary>
/// <param name="fileName">:ファイル名</param>
/// <param name="tag">:サウンドタグ</param>
/// <param name="isDim">:音の次元(デフォルト・2次元)</param>
/// <param name="volumeType">:音量タイプ(デフォルト・Bgm)</param>
void Sound::AddSound(std::string fileName, SoundTag tag, bool isDim,bool volumeType)
{
    //サウンドデータ設定
    SoundData sound = {};
    sound.volumeType = volumeType;
    sound.volume = FIRST_VOLUME;
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

/// <summary>
/// ドップラー効果
/// </summary>
/// <param name="tag">:タグ</param>
/// <param name="pos">:座標</param>
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
            const float SCALE = 60.0f;
            VECTOR soundVel = VScale(VSub(pos, prevSoundPos), SCALE);
            Set3DVelocitySoundMem(soundVel, sound.handle);
            VECTOR listnerVel = VScale(VSub(camera->GetPos(), prevListnerPos), SCALE);
            Set3DSoundListenerVelocity(listnerVel);

            //過去の座標に代入
            prevSoundPos = pos;
            prevListnerPos = camera->GetPos();
        };

    }
}

/// <summary>
/// 再生処理
/// </summary>
/// <param name="tag">:サウンドタグ</param>
/// <param name="soundType">:再生タイプ</param>
void Sound::StartSound(SoundTag tag, int playType)
{
    //再生されていなかったらサウンド再生
    auto& sound = soundData[tag];
    if (!CheckSoundMem(sound.handle))
    {
        //サウンドの有効範囲設定
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
/// 一度だけ再生処理
/// </summary>
/// <param name="tag">:サウンドタグ</param>
/// <param name="playType">:再生タイプ</param>
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

/// <summary>
/// 停止処理
/// </summary>
void Sound::StopSound(SoundTag tag)
{
    //サウンドが再生されていたら停止
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.handle))
    {
        StopSoundMem(sound.handle);
    }
}

/// <summary>
/// 全サウンド停止処理
/// </summary>
void Sound::StopAllSound()
{
    //すべてのサウンドに停止処理をする
    for (auto& tag : soundTagAll)
    {
        StopSound(tag);
    }
}

/// <summary>
/// 再生状態
/// </summary>
/// <returns>再生中:true|停止中:false</returns>
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

/// <summary>
/// コンストラクタ
/// </summary>
Sound::SoundData::SoundData()
    :handle(-1)
    , volume()
    , volumeType(false)
    , isDim(false)
    , playOnce(true)
{
}