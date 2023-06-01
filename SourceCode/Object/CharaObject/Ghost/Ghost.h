#pragma once

#include"Base/GhostBase.h"
#include"../../../Collision/Collision.h"

/* Ghost�̃N���X */
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
    void OnCollisionEnter(const ObjectBase* other)override;

    /// <summary>
    /// Ghost��]����
    /// </summary>
    void Rotate();

private:
    bool firstMove;
    bool nowMove;
    float moveCount;
    bool rotateNow;
    VECTOR aimDir;

    VECTOR aimPos;
    VECTOR holdPos;

    int lightHandle;
};

