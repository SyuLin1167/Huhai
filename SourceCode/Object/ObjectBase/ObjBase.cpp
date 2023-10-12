#include "ObjBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">:�I�u�W�F�N�g�^�O</param>
ObjBase::ObjBase(ObjTag tag)
    :objTag(tag)
    , rotateNow(false)
    , aimDir{ 0,0,0 }
    , objHandle(-1)
    , objPos(VGet(0,0,0))
    , objDir(VGet(1.0f, 0.0f, 0.0f))
    , objScale(VGet(0.1f, 0.1f, 0.1f))
    , objSpeed(20.0f)
    , isVisible(true)
    , isAlive(true)
    , colType()
    , colLine()
    , colSphere()
    , colCapsule()
    , colModel(-1)
{
    //�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjBase::~ObjBase()
{
    //�����Ȃ�
}

/// <summary>
/// ��]����
/// </summary>
void ObjBase::Rotate()
{
    if (rotateNow)
    {
        // ��]���ڕW�p�x�ɏ\���߂���Ή�]���[�h�I��
        if (IsSameAngle(aimDir, objDir))
        {
            objDir = aimDir;
            rotateNow = false;
        }
        else
        {
            // ��]������
            VECTOR interPolateDir;
            interPolateDir = RotForAimY(objDir, aimDir, ROTATE_VELOCITY);

            // ��]���ڕW�p�x�𒴂��Ă��Ȃ���
            VECTOR cross1, cross2;
            cross1 = VCross(objDir, aimDir);
            cross2 = VCross(interPolateDir, aimDir);

            //�ڕW�p�x�𒴂�����I��
            if (cross1.y * cross2.y < 0.0f)
            {
                interPolateDir = aimDir;
                rotateNow = false;
            }

            // �ڕW�x�N�g����10�x�����߂Â����p�x
            objDir = interPolateDir;
        }
    }
}

/// <summary>
/// �����蔻��X�V����
/// </summary>
void ObjBase::ColUpdate()
{
    //�S�����蔻��X�V
    colLine.Move(objPos);
    colSphere.Move(objPos);
    colCapsule.Move(objPos);

    if (colModel != -1)
    {
        MV1SetPosition(colModel, objPos);
        MV1SetupCollInfo(colModel);
    }
}