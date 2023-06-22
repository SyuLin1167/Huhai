#pragma once
#include<DxLib.h>

#include"../../ObjectBase/ObjectBase.h"

/* Player�N���X */
class Player :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Player();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Player();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    void OnCollisionEnter(const ObjBase* other)override;

    /// <summary>
    /// ���̂̏Փˎ�����
    /// </summary>
    /// <param name="colmodel">:�����蔻�胂�f��</param>
    void CollHitSphere(int colmodel);

    /// <summary>
    /// �����̏Փˎ�����
    /// </summary>
    /// <param name="colmodel">:�����蔻�胂�f��</param>
    void ColHitLine(int colmodel);

private:
    /// <summary>
    /// Player�ړ�����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Move(float deltaTime);


    VECTOR UP;                              //����
    VECTOR DOWN;                            //���
    VECTOR RIGHT;                           //�E
    VECTOR LEFT;                            //��

    VECTOR inputVec;						//�����x�N�g��
    VECTOR inputVel;						//���x�x�N�g��
    bool inputKey;							//�L�[���͔���
    bool canMove;                           //������

    VECTOR camFront;						//�J�����O����

    class Sound* plySound;                  //�T�E���h
};