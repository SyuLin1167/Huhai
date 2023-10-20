#pragma once

#include"Base/GhostBase.h"


/// <summary>
/// Ghost�N���X
/// </summary>
class Ghost :public GhostBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Ghost();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Ghost();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;


    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    void OnCollisionEnter(const ObjBase* other) override;
private:
    const float GHOST_MOVE_POS_Y = 1.2f;                                //�ړ�����Y���W

    float moveCount;                                                    //�J�E���g
    bool isFirstMove;                                                   //�������

    VECTOR aimPos;                                                      //�ڕW���W
    VECTOR holdPos;                                                     //�ꎞ�ۑ����W

    const float HIT_DISTANCE = 12.0f;                                   //�����蔻�苗��

    int lightHandle;                                                    //���C�g�n���h��
    const VECTOR LIGHT_POS = VGet(0.0f, 10.0f, 0.0f);                   //���C�g���W
    const float LIGHT_RANGE = 50.0f;                                    //���������L������
    const float LIGHT_ATTEN2 = 0.005f;                                  //���������W��
    const COLOR_F LIGHT_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);      //���C�g�̐F
};

