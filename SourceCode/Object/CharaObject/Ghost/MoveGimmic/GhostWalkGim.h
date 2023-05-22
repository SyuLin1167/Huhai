#pragma once

#include"../Base/GhostBase.h"

/*GhostWalkGim�̃N���X*/
class GhostWalkGim:public GhostBase
{
public:
    /// <summary>
    /// GhostWalkGim�R���X�g���N�^�[
    /// </summary>
    GhostWalkGim();
	
    /// <summary>
    /// GhostWalkGim�R���X�g���N�^�[
    /// </summary>
    ~GhostWalkGim();

    /// <summary>
    /// GhostWalkGim�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// GhostWalkGim�`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// GhostWalkGim�Փˎ�����
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    void OnCollisionEnter(const ObjectBase* other)override;

private:
    ObjectBase* light;

    bool move;
};

