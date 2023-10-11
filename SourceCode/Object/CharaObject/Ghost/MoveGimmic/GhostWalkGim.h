#pragma once

#include"../Base/GhostBase.h"

/// <summary>
/// GhostWalkGim�N���X
/// </summary>
class GhostWalkGim :public GhostBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GhostWalkGim();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~GhostWalkGim();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    void OnCollisionEnter(const ObjBase* other)override;

private:
    const VECTOR COL_LINE_HEIGHT = VGet(0, 5, 0);       //��������
    const VECTOR COL_LINE_FIRST_POS = VGet(7, 0, 0);    //�����n�_
};