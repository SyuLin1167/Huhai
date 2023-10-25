#pragma once
#include<DxLib.h>
#include<memory>

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// �v���C���[�I�u�W�F�N�g
/// </summary>
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
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    void OnCollisionEnter(const ObjBase* other) override;

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
    /// �ړ�����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Move(float deltaTime);


    VECTOR UP;                                      //����
    VECTOR DOWN;                                    //���
    VECTOR RIGHT;                                   //�E
    VECTOR LEFT;                                    //��

    VECTOR inputVec;                                //�����x�N�g��
    VECTOR inputVel;                                //���x�x�N�g��
    float walkStep;                                 //Y������
    bool inputKey;                                  //�L�[���͔���
    bool canMove;                                   //������

    const float HIT_DISTANCE = 12.0f;               //�����蔻�苗��
    const VECTOR HIT_AIM_POS = VGet(0, 18, 0);      //����㎋�_

    VECTOR camFront;                                //�J�����O����

    std::unique_ptr<class Sound> plySound;          //�T�E���h
};