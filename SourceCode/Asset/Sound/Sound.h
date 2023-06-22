#pragma once

#include<DxLib.h>
#include<unordered_map>
#include<string>

#include"SoundTag.h"

/*Soundクラス*/
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
    /// <param name="volume">:音量</param>
    /// <param name="isDim">:音の次元(デフォルト・2次元)</param>
    void AddSound(std::string fileName, SoundTag tag, int volume, bool isDim = false);

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="pos"></param>
    void Update(VECTOR pos);

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
    /// サウンド一個分のデータ構造体
    /// </summary>
    struct SoundData
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SoundData();

        int handle;        //サウンドハンドル
        int volume;             //音量
        bool isDim;             //次元
        bool playOnce;         //再生回数
    };

private:
    int soundType;                                          //サウンドID
    int attachedIndex;                                      //アタッチ後のインデックス
    
    float nowSoundTime;                                     //現在のサウンド時刻

    std::unordered_map<SoundTag, SoundData> soundData;      //サウンドデータ
};

