#pragma once

#include<DxLib.h>
#include<string>
#include<vector>

/// <summary>
/// ���f���̃A�j���[�V�����Ǘ�
/// </summary>
class Animation
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="modelHandle">:���f���n���h��</param>
    Animation(int modelHandle);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Animation();

    /// <summary>
    /// �ǉ�����
    /// </summary>
    /// <param name="fileName">:�t�@�C����</param>
    /// <param name="animSpeed">:�Đ����x(�f�t�H���g�E30fps)</param>
    /// <param name="loopState">:���[�v���(�f�t�H���g�E���[�v������)</param>
    /// <returns>animData�z��̓Y�����ԍ�</returns>
    int AddAnimation(std::string fileName, float animSpeed = 30.0f, bool loopState = true);

    /// <summary>
    /// �A�j���[�V�������Ԍo��
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void AddAnimTime(float deltaTime);

    /// <summary>
    /// �Đ�����
    /// </summary>
    /// <param name="animId">:�A�j���[�V����ID</param>
    void StartAnim(int animID);

    /// <summary>
    /// ��~����
    /// </summary>
    void StopAnim();

    /// <summary>
    /// �Đ����
    /// </summary>
    /// <returns>�Đ���:true|��~��:false</returns>
    bool IsPlaying();

    /// <summary>
    /// �A�j���[�V�����f�[�^
    /// </summary>
    struct AnimData
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        AnimData();

        int handle;                     //�A�j���[�V�����n���h��
        int index;                      //�A�^�b�`����A�j���[�V�����ԍ�
        float totalTime;                //���Đ�����
        float speed;                    //�Đ����x
        bool isLoop;                    //���[�v�Đ����邩�ǂ���
    };

private:
    int modelHandle;                    //���f���n���h��
    int nowAnimType;                    //���݂̃A�j���[�V����ID

    int attachedIndex;                  //�A�^�b�`��̃C���f�b�N�X

    float nowAnimTime;                  //���݂̃A�j���[�V��������

    std::vector<AnimData> animData;     //�A�j���[�V���������o�^�p
};
