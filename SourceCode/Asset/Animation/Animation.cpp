#include "Animation.h"
#include"../AssetManager/AssetManager.h"

Animation::Animation(int modelHandle)
    :modelHandle(modelHandle)
    , nowAnimType(-1)
    , nowAnimTime(0.0f)
    , attachedIndex(0)
{
}

Animation::~Animation()
{
    //データ削除
    animData.clear();
}

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

void Animation::StopAnim()
{
    //アニメーション時刻を総再生時間にする
    nowAnimTime = animData[nowAnimType].totalTime;
}

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

Animation::AnimData::AnimData()
    :handle(-1)
    , index(-1)
    , totalTime(0.0f)
    , speed(0.0f)
    , isLoop(false)
{
    //処理なし
}


