#include "Animation.h"
#include"../AssetManager/AssetManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="modelHandle">:���f���n���h��</param>
Animation::Animation(int modelHandle)
    :modelHandle(modelHandle)
    , nowAnimType(-1)
    , nowAnimTime(0.0f)
    , attachedIndex(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Animation::~Animation()
{
    //�f�[�^�폜
    animData.clear();
}

/// <summary>
/// �ǉ�����
/// </summary>
/// <param name="fileName">:�t�@�C����</param>
/// <param name="animSpeed">:�Đ����x(�f�t�H���g�E30fps)</param>
/// <param name="loopState">:���[�v���(�f�t�H���g�E���[�v������)</param>
/// <returns>animData�z��̓Y�����ԍ�</returns>
int Animation::AddAnimation(std::string fileName, float animSpeed, bool loopState)
{
    //�A�j���[�V�����f�[�^�ݒ�
    AnimData anim = {};
    anim.speed = animSpeed;
    anim.isLoop = loopState;

    //�A�j���[�V�����o�^&�擾
    anim.handle = AssetManager::GetAnim(fileName.c_str());

    //���g���󂾂����炻�̂܂ܕԂ�
    if (anim.handle == -1)
    {
        return -1;
    }

    //�A�j���[�V�����̌�����C���f�b�N�X�擾���ăA�^�b�`
    anim.index = MV1GetAnimNum(anim.handle) - 1;
    attachedIndex = MV1AttachAnim(modelHandle, anim.index,
        anim.handle, TRUE);

    //�A�j���[�V�����Đ����Ԏ擾
    anim.totalTime = MV1GetAnimTotalTime(anim.handle, anim.index);

    //�܂��Đ����Ȃ��̂ŁA�f�^�b�`
    MV1DetachAnim(modelHandle, attachedIndex);

    //�f�[�^�ɒǉ����ēY�����ԍ��Ԃ�
    animData.push_back(anim);
    return static_cast<int>(animData.size() - 1);
}

/// <summary>
/// �A�j���[�V�������Ԍo��
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
void Animation::AddAnimTime(float deltaTime)
{
    //���ݎ��ԂɌ��݂̃A�j���[�V�����t���[�������Z
    nowAnimTime += animData[nowAnimType].speed * deltaTime;

    //���[�v�Đ�������Ȃ玞�ԃ��Z�b�g
    if (animData[nowAnimType].isLoop &&
        nowAnimTime > animData[nowAnimType].totalTime)
    {
        nowAnimTime = 0.0f;
    }

    //�A�j���[�V�������ԃA�^�b�`
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}

/// <summary>
/// �Đ�����
/// </summary>
/// <param name="animId">:�A�j���[�V����ID</param>
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
        attachedIndex = MV1AttachAnim(modelHandle, animData[animID].index,
            animData[nowAnimType].handle, TRUE);
    }

    //���Ԃ����Z�b�g���ăA�j���[�V�������ԃA�^�b�`
    nowAnimTime = 0.0f;
    MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
}


/// <summary>
/// ��~����
/// </summary>
void Animation::StopAnim()
{
    //�A�j���[�V���������𑍍Đ����Ԃɂ���
    nowAnimTime = animData[nowAnimType].totalTime;
}

/// <summary>
/// �Đ����
/// </summary>
/// <returns>�Đ���:true|��~��:false</returns>
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

/// <summary>
/// �R���X�g���N�^
/// </summary>
Animation::AnimData::AnimData()
    :handle(-1)
    , index(-1)
    , totalTime(0.0f)
    , speed(0.0f)
    , isLoop(false)
{
}


