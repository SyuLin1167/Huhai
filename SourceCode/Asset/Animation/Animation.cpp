#include "Animation.h"
#include"../AssetManager/AssetManager.h"

// �R���X�g���N�^ //

Animation::Animation(int modelHandle)
    :modelHandle(modelHandle)
    , nowAnimType(-1)
    , nowAnimTime(0.0f)
    , attachedIndex(0)
{
}

// �f�X�g���N�^ //

Animation::~Animation()
{
    //�f�[�^�폜
    while (animData.size() == 0)
    {
        animData.pop_back();
    }
}

// �ǉ����� //

int Animation::AddAnimation(std::string fileName, float Fps, bool loopState)
{
    //�A�j���[�V�����f�[�^�ݒ�
    AnimData anim = {};
    anim.animFps = Fps;
    anim.isLoop = loopState;

    //�A�j���[�V�����o�^&�擾
    anim.animHandle = AssetManager::GetAnim(fileName.c_str());

    //���g���󂾂����炻�̂܂ܕԂ�
    if (anim.animHandle == -1)
    {
        return -1;
    }

    //�A�j���[�V�����̌�����C���f�b�N�X�擾���ăA�^�b�`
    anim.animIndex = MV1GetAnimNum(anim.animHandle) - 1;
    attachedIndex = MV1AttachAnim(modelHandle, anim.animIndex,
        anim.animHandle, TRUE);

    //�A�j���[�V�����Đ����Ԏ擾
    anim.totalTime = MV1GetAnimTotalTime(anim.animHandle, anim.animIndex);

    //�܂��Đ����Ȃ��̂ŁA�f�^�b�`
    MV1DetachAnim(modelHandle, attachedIndex);

    //�f�[�^�ɒǉ����ēY�����ԍ��Ԃ�
    animData.push_back(anim);
    return static_cast<int>(animData.size() - 1);                                               //vector�ɓ���Y�����ԍ���Ԃ�
}

// �A�j���[�V�������Ԍo�� //

void Animation::AddAnimTime(float deltaTime)
{
    //���ݎ��ԂɌ��݂̃A�j���[�V�����t���[�������Z
    nowAnimTime += animData[nowAnimType].animFps * deltaTime;

    //���[�v�Đ�������Ȃ玞�ԃ��Z�b�g
    if (animData[nowAnimType].isLoop &&
        nowAnimTime > animData[nowAnimType].totalTime)
    {
        nowAnimTime = 0.0f;
    }

    //�A�j���[�V�������ԃA�^�b�`
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}

// �Đ����� //

void Animation::StartAnim(int animID)
{
    //�ȑO�̃A�j���[�V�����ƈ���Ă�����V�������ɍ����ւ���
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

    //���Ԃ����Z�b�g���ăA�j���[�V�������ԃA�^�b�`
    nowAnimTime = 0.0f;
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}

    // ��~���� //

void Animation::StopAnim()
{
    //�A�j���[�V���������𑍍Đ����Ԃɂ���
    nowAnimTime = animData[nowAnimType].totalTime;
}

// �Đ���� //

bool Animation::IsPlaying()
{
    //���[�v�Đ��s�ŁA���������Đ����Ԃ𒴂������~���ɂ���
    if (!animData[nowAnimType].isLoop && nowAnimTime > animData[nowAnimType].totalTime)
    {
        return false;
    }

    //��{�͍Đ����ɂ���
    return true;
}

// �R���X�g���N�^ //

Animation::AnimData::AnimData()
    :animHandle(-1)
    , animIndex(-1)
    , totalTime(-1.0f)
    , animFps(0.0f)
    , isLoop(false)
{
}


