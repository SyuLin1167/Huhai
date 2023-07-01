#include "Ghost.h"
#include"../Player/Player.h"
#include"../../MapObject/Light/FlashLight/FlashLight.h"

/* �R���X�g���N�^ */

Ghost::Ghost()
    :GhostBase()
    , moveCount(7.0f)
    , isFirstMove(true)
    , isMove(false)
    , rotateNow(false)
    ,aimPos(VGet(0.0f, 0.0f, 0.0f))
    , aimDir(VGet(0.0f, 0.0f, 1.0f))
    , lightHandle(-1)
    , holdPos(VGet(0.0f, 0.0f, 0.0f))
{
    objPos = VGet(0.0f, 0.0f, -45.0f);

    //�A�j���[�V�����ݒ�
    if (animType != SAD)
    {
        animType = SAD;
        gstAnim->StartAnim(animType);
    }

    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5.0f, 0);
    colSphere.Radius = 3.0f;
    colSphere.worldCenter = objPos;
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -5.0f, 0.0f));

    //�ړ����x
    objSpeed = 13.0f;

    //�T�E���h�ݒ�
    gstSound->StartSound(SoundTag::Escape, DX_PLAYTYPE_LOOP);
}

// �f�X�g���N�^ //

Ghost::~Ghost()
{
    //���C�g�폜
    DeleteLightHandle(lightHandle);

    //���f���폜
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
}

// �X�V���� //

void Ghost::Update(float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    gstAnim->AddAnimTime(deltaTime);

    //���f����]
    MATRIX rotMatY = MGetRotY(180 * (float)(DX_PI / 180.0f));
    VECTOR negativeVec = VTransform(objDir, rotMatY);
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
    rotateNow = true;
    Rotate();

    //�������͎w����W�ֈړ�
    if (moveCount >= 0.0f)
    {
        moveCount -= deltaTime;
    }
    //�J�E���g���[���ɂȂ����瓮��J�n
    else if (isFirstMove)
    {
        //�A�j���[�V����&�T�E���h�Đ�
        if (animType != MOVE)
        {
            animType = MOVE;
            gstAnim->StartAnim(animType);

            //���C�g�ݒu
            ObjManager::GetFirstObj(ObjectTag::Light)->SetAlive(false);
            lightHandle = CreatePointLightHandle(objPos, 50.0f, 0.0f, 0.0f, 0.005f);
            SetLightDifColorHandle(lightHandle, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));

            gstSound->StartSound(SoundTag::GhostScream, DX_PLAYTYPE_BACK);
        }
        //�ڕW���W�ɋ߂Â����珉���I��
        if (abs(VSize(aimPos - objPos)) < 2.0f)
        {
            isFirstMove = false;
        }
        isMove = true;
    }
    else
    {
        //��{�ڕW���W�̓v���C���[���W
        aimPos = ObjManager::GetFirstObj(ObjectTag::Player)->GetPos();
    }

    //���쒆�͖ڕW���W�Ɍ������Ĉړ�
    if (isMove)
    {
        VECTOR moveVec = aimPos - objPos;
        moveVec = VNorm(moveVec);
        objPos += moveVec * objSpeed * deltaTime;
        aimDir = moveVec;
        objPos.y = 1.2f;
    }
    MV1SetPosition(objHandle, objPos);                        //�|�W�V�����ݒ�

    //���C�g�X�V
    if (lightHandle)
    {
        SetLightPositionHandle(lightHandle, objPos + VGet(0.0f, 10.0f, 0.0f));
    }

    //�����蔻��X�V
    ColUpdate();

    //�T�E���h�X�V
    gstSound->Doppler(SoundTag::GhostScream, objPos);
    gstSound->Doppler(SoundTag::Escape, objPos);
}

// �`�揈�� //

void Ghost::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}

// �����蔻�菈�� //

void Ghost::OnCollisionEnter(const ObjBase* other)
{
    ObjectTag tag = other->GetTag();

    //�����ɂԂ������牟���߂�
    if (tag == ObjectTag::Map)
    {
        int colModel = other->GetColModel();
        //���̂̓����蔻��
        MV1_COLL_RESULT_POLY_DIM colInfo;
        if (CollisionPair(colSphere, colModel, colInfo))
        {
            VECTOR pushBack = CalcSpherePushBackFromMesh(colSphere, colInfo);
            objPos += pushBack;
            MV1CollResultPolyDimTerminate(colInfo);
            ColUpdate();
        }

        //�����̓����蔻��
        MV1_COLL_RESULT_POLY colInfoLine;
        if (CollisionPair(colLine, colModel, colInfoLine))
        {
            objPos = colInfoLine.HitPosition;
            ColUpdate();
        }
    }

    //�v���C���[�ɓ���������Q�[���I�[�o�[�ɂ���
    if (tag == ObjectTag::Player)
    {
        if (abs(VSize(other->GetPos() - objPos)) < 12.0f && !isFirstMove)
        {
            if (animType != SAD)
            {
                animType = SAD;
                gstAnim->StartAnim(animType);
            }
            isMove = false;
            aimDir = VScale(VNorm(aimPos - objPos), 0.1f);
            ColUpdate();
        }
    }

}

// ��]���� //

void Ghost::Rotate()
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
            interPolateDir = RotForAimY(objDir, aimDir, 5.0f);

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