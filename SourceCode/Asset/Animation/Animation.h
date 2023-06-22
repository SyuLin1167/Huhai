#pragma once

#include<DxLib.h>
#include<string>
#include<vector>

/* Animationクラス */
class Animation
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="modelHandle">:モデルハンドル</param>
    Animation(int modelHandle);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Animation();

    /// <summary>
    /// 追加処理
    /// </summary>
    /// <param name="fileName">:ファイル名</param>
    /// <param name="Fps">:再生速度(デフォルト・30fps)</param>
    /// <param name="loopState">:ループ状態(デフォルト・ループさせる)</param>
    /// <returns>animData配列の添え字番号</returns>
    int AddAnimation(std::string fileName, float Fps = 30.0f, bool loopState = true);

    /// <summary>
    /// アニメーション時間経過
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void AddAnimTime(float deltaTime);

    /// <summary>
    /// 再生処理
    /// </summary>
    /// <param name="animId">:アニメーションID</param>
    void StartAnim(int animID);

    /// <summary>
    /// 停止処理
    /// </summary>
    void StopAnim();

    /// <summary>
    /// 再生状態
    /// </summary>
    /// <returns>再生中:true|停止中:false</returns>
    bool IsPlaying();

    /* アニメーション１個分のデータ構造体 */
    struct AnimData
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        AnimData();

        int animHandle;					//アニメーションハンドル
        int animIndex;					//アタッチするアニメーション番号
        float totalTime;				//総再生時間
        float animFps;					//再生速度
        bool isLoop;					//ループ再生するかどうか
    };
private:
    int modelHandle;					//モデルハンドル
    int nowAnimType;					//現在のアニメーションID

    int attachedIndex;					//アタッチ後のインデックス

    float nowAnimTime;					//現在のアニメーション時刻

    std::vector<AnimData> animData;		//アニメーション複数登録用
};
