#pragma once

#include"../Base/GhostBase.h"

/*GhostMoveGim�̃N���X*/
class GhostMoveGim:public GhostBase
{
public:
    /// <summary>
    /// GhostMoveGim�R���X�g���N�^�[
    /// </summary>
    GhostMoveGim();
	
    /// <summary>
    /// GhostMoveGim�R���X�g���N�^�[
    /// </summary>
    ~GhostMoveGim();

    /// <summary>
    /// GhostMoveGim�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// GhostMoveGim�`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// GhostMoveGim�Փˎ�����
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    void OnCollisionEnter(const ObjectBase* other)override;

private:
    ObjectBase* light;

    bool move;
};

