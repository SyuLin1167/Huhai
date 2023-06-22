#pragma once

#include"Base/GhostBase.h"


/* Ghost�N���X */
class Ghost :public GhostBase
{
public:
    /// <summary>
    /// Ghost�̃R���X�g���N�^�[
    /// </summary>
    Ghost();

    /// <summary>
    /// Ghost�̃f�X�g���N�^�[
    /// </summary>
    ~Ghost();

    /// <summary>
    /// Ghost�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Ghost�`�揈��
    /// </summary>
    void Draw()override;


    /// <summary>
    /// Ghost�Փˎ�����
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    void OnCollisionEnter(const ObjBase* other)override;

    /// <summary>
    /// Ghost��]����
    /// </summary>
    void Rotate();

private:
    float moveCount;        //�J�E���g
    bool isFirstMove;       //�������
    bool isMove;            //�ړ����

    VECTOR aimDir;          //�ڕW����
    bool rotateNow;         //��]���

    VECTOR aimPos;          //�ڕW���W
    VECTOR holdPos;         //�ꎞ�ۑ����W

    int lightHandle;        //���C�g�n���h��
};

