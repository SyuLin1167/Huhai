#include "Animation.h"
#include"../AssetManager/AssetManager.h"

// コンストラクタ //

Animation::Animation(int modelHandle)
    :modelHandle(modelHandle)
    , nowAnimType(-1)
    , nowAnimTime(0.0f)
    , attachedIndex(0)
{
}

// デストラクタ //

Animation::~Animation()
{
    //データ削除
    while (animData.size() == 0)
    {
        animData.pop_back();
    }
}

// 追加処理 //

int Animation::AddAnimation(std::string fileName, float Fps, bool loopState)
{
    //アニメーションデータ設定
    AnimData anim = {};
    anim.animFps = Fps;
    anim.isLoop = loopState;

    //アニメーション登録&取得
    anim.animHandle = AssetManager::GetAnim(fileName.c_str());

    //中身が空だったらそのまま返す
    if (anim.animHandle == -1)
    {
        return -1;
    }

    //アニメーションの個数からインデックス取得してアタッチ
    anim.animIndex = MV1GetAnimNum(anim.animHandle) - 1;
    attachedIndex = MV1AttachAnim(modelHandle, anim.animIndex,
        anim.animHandle, TRUE);

    //アニメーション再生時間取得
    anim.totalTime = MV1GetAnimTotalTime(anim.animHandle, anim.animIndex);

    //まだ再生しないので、デタッチ
    MV1DetachAnim(modelHandle, attachedIndex);

    //データに追加して添え字番号返す
    animData.push_back(anim);
    return static_cast<int>(animData.size() - 1);                                               //vectorに入る添え字番号を返す
}

// アニメーション時間経過 //

void Animation::AddAnimTime(float deltaTime)
{
    //現在時間に現在のアニメーションフレームを加算
    nowAnimTime += animData[nowAnimType].animFps * deltaTime;

    //ループ再生させるなら時間リセット
    if (animData[nowAnimType].isLoop &&
        nowAnimTime > animData[nowAnimType].totalTime)
    {
        nowAnimTime = 0.0f;
    }

    //アニメーション時間アタッチ
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}

// 再生処理 //

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
        attachedIndex = MV1AttachAnim(modelHandle, animData[animID].animIndex,
            animData[nowAnimType].animHandle, TRUE);
    }

    //時間をリセットしてアニメーション時間アタッチ
    nowAnimTime = 0.0f;
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}

    // 停止処理 //

void Animation::StopAnim()
{
    //アニメーション時刻を総再生時間にする
    nowAnimTime = animData[nowAnimType].totalTime;
}

// 再生状態 //

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

// コンストラクタ //

Animation::AnimData::AnimData()
    :animHandle(-1)
    , animIndex(-1)
    , totalTime(-1.0f)
    , animFps(0.0f)
    , isLoop(false)
{
}


