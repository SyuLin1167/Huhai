#include "Animation.h"
#include"../AssetManager/AssetManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="modelHandle">:モデルハンドル</param>
Animation::Animation(int modelHandle)
    :modelHandle(modelHandle)
    , nowAnimType(-1)
    , nowAnimTime(0.0f)
    , attachedIndex(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Animation::~Animation()
{
    //データ削除
    animData.clear();
}

/// <summary>
/// 追加処理
/// </summary>
/// <param name="fileName">:ファイル名</param>
/// <param name="animSpeed">:再生速度(デフォルト・30fps)</param>
/// <param name="loopState">:ループ状態(デフォルト・ループさせる)</param>
/// <returns>animData配列の添え字番号</returns>
int Animation::AddAnimation(std::string fileName, float animSpeed, bool loopState)
{
    //アニメーションデータ設定
    AnimData anim = {};
    anim.speed = animSpeed;
    anim.isLoop = loopState;

    //アニメーション登録&取得
    anim.handle = AssetManager::GetAnim(fileName.c_str());

    //中身が空だったらそのまま返す
    if (anim.handle == -1)
    {
        return -1;
    }

    //アニメーションの個数からインデックス取得してアタッチ
    anim.index = MV1GetAnimNum(anim.handle) - 1;
    attachedIndex = MV1AttachAnim(modelHandle, anim.index,
        anim.handle, TRUE);

    //アニメーション再生時間取得
    anim.totalTime = MV1GetAnimTotalTime(anim.handle, anim.index);

    //まだ再生しないので、デタッチ
    MV1DetachAnim(modelHandle, attachedIndex);

    //データに追加して添え字番号返す
    animData.push_back(anim);
    return static_cast<int>(animData.size() - 1);
}

/// <summary>
/// アニメーション時間経過
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void Animation::AddAnimTime(float deltaTime)
{
    //現在時間に現在のアニメーションフレームを加算
    nowAnimTime += animData[nowAnimType].speed * deltaTime;

    //ループ再生させるなら時間リセット
    if (animData[nowAnimType].isLoop &&
        nowAnimTime > animData[nowAnimType].totalTime)
    {
        nowAnimTime = 0.0f;
    }

    //アニメーション時間アタッチ
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}

/// <summary>
/// 再生処理
/// </summary>
/// <param name="animId">:アニメーションID</param>
void Animation::StartAnim(int animID)
{
    //以前のアニメーションと違っていたら新しい方に差し替える
    if (animID != nowAnimType)
    {
        if (nowAnimType != -1)
        {
            MV1DetachAnim(modelHandle, attachedIndex);
        }

        nowAnimType = animID;
        attachedIndex = MV1AttachAnim(modelHandle, animData[animID].index,
            animData[nowAnimType].handle, TRUE);
    }

    //時間をリセットしてアニメーション時間アタッチ
    nowAnimTime = 0.0f;
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}


/// <summary>
/// 停止処理
/// </summary>
void Animation::StopAnim()
{
    //アニメーション時刻を総再生時間にする
    nowAnimTime = animData[nowAnimType].totalTime;
}

/// <summary>
/// 再生状態
/// </summary>
/// <returns>再生中:true|停止中:false</returns>
bool Animation::IsPlaying()
{
    //ループ再生不可で、時刻が総再生時間を超えたら停止中にする
    if (!animData[nowAnimType].isLoop && nowAnimTime > animData[nowAnimType].totalTime)
    {
        return false;
    }

    //基本は再生中にする
    return true;
}

/// <summary>
/// コンストラクタ
/// </summary>
Animation::AnimData::AnimData()
    :handle(-1)
    , index(-1)
    , totalTime(0.0f)
    , speed(0.0f)
    , isLoop(false)
{
}


