#pragma once
#include<DxLib.h>
#include<unordered_map>
#include<string>

#include"SoundTag.h"
using namespace std;

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
    /// <param name="soundFileName">:サウンドファイル名</param>
    void AddSound(string soundFileName, SoundTag tag, int volume,bool isDimension=false);

    void Update(VECTOR targetPos);

    /// <summary>
    /// 再生処理
    /// </summary>
    /// <param name="soundType">:サウンドタイプ</param>
    void StartSound(SoundTag tag, int playType);
    void StartSoundOnce(SoundTag tag, int playType);


    /// <summary>
    /// 停止処理
    /// </summary>
    void StopSound(SoundTag tag);
    void StopAllSound();

    /// <summary>
    /// 再生中かどうか
    /// </summary>
    /// <returns>再生状態</returns>
    bool IsPlaying(SoundTag tag);

    struct SoundData
    {
    public:
        /// <summary>
        /// SoundDataコンストラクタ
        /// </summary>
        SoundData();

        int soundHandle;        //サウンドハンドル
        int volume;
        bool isDimension;
        bool soundOnce;
    };

private:
    unordered_map<SoundTag, SoundData> soundData;
    int soundType;              //サウンドID
    int attachedIndex;          //アタッチ後のインデックス
    float nowSoundTime;          //現在のサウンド時刻
};

