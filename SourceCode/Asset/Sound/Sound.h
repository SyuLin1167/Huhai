#pragma once
#include<DxLib.h>
#include<unordered_map>
#include<string>

#include"SoundTag.h"

/// <summary>
/// サウンドの管理
/// </summary>
class Sound
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Sound();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Sound();

    /// <summary>
    /// 追加処理
    /// </summary>
    /// <param name="fileName">:ファイル名</param>
    /// <param name="tag">:サウンドタグ</param>
    /// <param name="isDim">:音の次元(デフォルト・2次元)</param>
    /// <param name="volumeType">:音量タイプ(デフォルト・Bgm)</param>
    void AddSound(std::string fileName, SoundTag tag, bool isDim = false, bool volumeType = false);

    /// <summary>
    /// ドップラー効果
    /// </summary>
    /// <param name="tag">:タグ</param>
    /// <param name="pos">:座標</param>
    void Doppler(SoundTag tag, VECTOR pos);

    /// <summary>
    /// 再生処理
    /// </summary>
    /// <param name="tag">:サウンドタグ</param>
    /// <param name="soundType">:再生タイプ</param>
    void StartSound(SoundTag tag, int playType);

    /// <summary>
    /// 一度だけ再生処理
    /// </summary>
    /// <param name="tag">:サウンドタグ</param>
    /// <param name="playType">:再生タイプ</param>
    void StartSoundOnce(SoundTag tag, int playType);


    /// <summary>
    /// 停止処理
    /// </summary>
    void StopSound(SoundTag tag);

    /// <summary>
    /// 全サウンド停止処理
    /// </summary>
    void StopAllSound();

    /// <summary>
    /// 再生状態
    /// </summary>
    /// <returns>再生中:true|停止中:false</returns>
    bool IsPlaying(SoundTag tag);

    /// <summary>
    /// サウンドデータ
    /// </summary>
    struct SoundData
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SoundData();

        int handle;             //サウンドハンドル
        int volume;             //音量
        bool volumeType;        //音量タイプ
        bool isDim;             //次元
        bool playOnce;          //再生回数
    };

private:
    const int FIRST_VOLUME = 150;                           //初期音量
    const float RADIUS_SOUND = 500.0f;                      //サウンド範囲

    int soundType;                                          //サウンドID
    int attachedIndex;                                      //アタッチ後のインデックス
    
    float nowSoundTime;                                     //現在のサウンド時刻

    VECTOR prevSoundPos;                                    //過去のサウンド座標
    VECTOR prevListnerPos;                                  //過去のリスナー座標

    std::unordered_map<SoundTag, SoundData> soundData;      //サウンドデータ
};

