#include "Animation.h"
#include"../AssetManager/AssetManager.h"

    // @brief Animationコンストラクター //

Animation::Animation(int modelHandle)
    :modelHandle(modelHandle)
    , nowAnimType(-1)
    , nowAnimTime(0.0f)
    , attachedIndex(0)
{
}

    // @brief Animationデストラクター //

Animation::~Animation()
{
}

    // @brief アニメーション追加処理 //

int Animation::AddAnimation(std::string animFileName, float animFps, bool animLoop)
{
    AnimData anim = {};                                                                     //アニメーションデータ
    anim.animFps = animFps;                                                                 //フレームレートは引数から代入
    anim.isLoop = animLoop;                                                                 //ループ再生フラグは引数から代入

    anim.animHandle = AssetManager::GetAnim(animFileName.c_str());                          //アニメーションデータ読み込み
    if (anim.animHandle == -1)                                                              //データが入っていなかったら
    {
        return -1;                                                                          //入っていないという結果を返す
    }

    anim.animIndex = MV1GetAnimNum(anim.animHandle) - 1;                                    //アニメーションの個数からインデックスを得る

    attachedIndex = MV1AttachAnim(modelHandle, anim.animIndex,
        anim.animHandle, TRUE);                                          //アニメーションをモデルに追加

    anim.totalTime = MV1GetAnimTotalTime(anim.animHandle, anim.animIndex);                //アニメーション再生時間取得

    //このアニメはまだ再生しないので、異端アニメーション解除
    MV1DetachAnim(modelHandle, attachedIndex);

    animData.push_back(anim);                                                           //末尾にアニメーションデータ追加

    return static_cast<int>(animData.size() - 1);                                               //vectorに入る添え字番号を返す
}

    // @brief アニメーション時間セット //

void Animation::AddAnimTime(float deltaTime)
{
    nowAnimTime += animData[nowAnimType].animFps * deltaTime;                               //現在時間に現在のアニメーションフレームを加算

    if (animData[nowAnimType].isLoop &&
        nowAnimTime > animData[nowAnimType].totalTime)                                      //現在時間がアニメーションの総再生数を超えてループ再生させるなら
    {
        nowAnimTime = 0.0f;                                                                 //時間リセット
    }
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}

    // @brief アニメーション再生 //

void Animation::StartAnim(int animID)
{
    if (animID != nowAnimType)                                                              //以前のアニメーションと違っていたら
    {
        if (nowAnimType != -1)                                                              //現在のアニメーションが空じゃなかったら
        {
            MV1DetachAnim(modelHandle, attachedIndex);                                      //デタッチ
        }

        nowAnimType = animID;                                                               //以前のアニメーションとする
        attachedIndex = MV1AttachAnim(modelHandle, animData[animID].animIndex,
            animData[nowAnimType].animHandle, TRUE);                                        //アニメーションをアタッチ
    }

    nowAnimTime = 0.0f;                                                                     //時間リセット
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);                          //アタッチしているアニメーションの時間設定
}

    // @brief アニメーション停止 //

void Animation::StopAnim()
{
    nowAnimTime = animData[nowAnimType].totalTime;                                          //アニメーション時刻を総再生時間にする
}

    // @brief 再生中かどうか //

bool Animation::IsPlaying()
{
    if (!animData[nowAnimType].isLoop && nowAnimTime > animData[nowAnimType].totalTime)      //ループ再生不可で、時刻が総再生時間を超えたら
    {
        return false;                                                                       //再生中でないfalseを返す
    }
    return true;                                                                            //基本は再生中のtrueを返す
}

    // @brief AnimDataコンストラクタ― //

Animation::AnimData::AnimData()
    :animHandle(-1)
    , animIndex(-1)
    , totalTime(-1.0f)
    , animFps(0.0f)
    , isLoop(false)
{
}


