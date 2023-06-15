#include "Ghost.h"
#include"../Player/Player.h"
#include"../../MapObject/Light/FlashLight/FlashLight.h"

        /* @brief Ghost�R���X�g���N�^ */

Ghost::Ghost()
    :GhostBase()
    , moveCount(0.0f)
    , firstMove(true)
    , nowMove(false)
    , rotateNow(false)
    , aimDir(VGet(0.0f, 0.0f, 1.0f))
    , lightHandle(-1)
    , holdPos(VGet(0.0f, 0.0f, 0.0f))
{
    if (animType != SAD)
    {
        animType = SAD;
        gstAnim->StartAnim(animType);
    }
    objPos = VGet(0.0f, 0.0f, -45.0f);

    //---�����蔻�苅�ݒ�---//
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5.0f, 0);			//���[�J�����W
    colSphere.Radius = 3.0f;						//�����a
    colSphere.worldCenter = objPos;					//���[���h���W

    //---�����蔻������ݒ�---//
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -5.0f, 0.0f));             //�����ݒ�

    objSpeed = 13.0f;

}

        // @brief Ghost�f�X�g���N�^ //

Ghost::~Ghost()
{
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
}

        // @brief Ghost�X�V���� //

void Ghost::Update(float deltaTime)
{
    gstAnim->AddAnimTime(deltaTime);
    gstSound->Update(objPos);
    MATRIX rotMatY = MGetRotY(180 * (float)(DX_PI / 180.0f));       //�������ɉ�]������
    objDir.y = 0;
    VECTOR negativeVec = VTransform(objDir, rotMatY);
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);         //���f����]

    rotateNow = true;
    Rotate();


    if (firstMove)
    {
        moveCount += deltaTime;
        if (moveCount >= 7.0f)
        {
            nowMove = true;
            if (animType != MOVE)
            {
                animType = MOVE;
                gstAnim->StartAnim(animType);
                gstSound->StartSound(SoundTag::GhostScream, DX_PLAYTYPE_BACK);
                ObjManager::GetFirstObj(ObjectTag::Light)->SetAlive(false);
                lightHandle = CreatePointLightHandle(objPos, 50.0f, 0.0f, 0.0f, 0.005f);
                SetLightDifColorHandle(lightHandle, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
                aimPos = VGet(0.0f, 0.0f, 0.0f);
            }
            if (abs(VSize(aimPos - objPos)) < 2.0f)
            {
                firstMove = false;
            }
        }
    }
    else
    {
        aimPos = ObjManager::GetFirstObj(ObjectTag::Player)->GetPos();
    }

    if (nowMove)
    {
        VECTOR moveVec = aimPos - objPos;
        moveVec = VNorm(moveVec);
        objPos += moveVec * objSpeed * deltaTime;
        aimDir = moveVec;
    }

    if (lightHandle)
    {
        SetLightPositionHandle(lightHandle, objPos + VGet(0.0f, 10.0f, 0.0f));
    }

    MV1SetPosition(objHandle, objPos);                        //�|�W�V�����ݒ�

    ColUpdate();            //�����蔻��̈ړ�
}

        // @brief Ghost�`�揈�� //

void Ghost::Draw()
{
    MV1DrawModel(objHandle);
}

        // @brief Ghost�Փˎ����� //

void Ghost::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();

    if (tag == ObjectTag::Map)                                      //�}�b�v�ƂԂ�������
    {
        int colModel = other->GetColModel();                        //���f�������蔻��擾

        //---�}�b�v�Ƌ��E���s�̓����蔻��---//
        MV1_COLL_RESULT_POLY_DIM colInfo;                          //���f�������蔻����
        if (CollisionPair(colSphere, colModel, colInfo))
        {
            VECTOR pushBack = CalcSpherePushBackFromMesh(colSphere, colInfo);   //�����߂��ʎZ�o
            objPos += pushBack;                                                         //�����߂�
            MV1CollResultPolyDimTerminate(colInfo);                        //�����蔻������
            ColUpdate();
        }

        //---�}�b�v�Ƒ��������̓����蔻��---//
        MV1_COLL_RESULT_POLY colInfoLine;                           //���������蔻����
        if (CollisionPair(colLine, colModel, colInfoLine))
        {
            objPos = colInfoLine.HitPosition;                       //�������Փˎ��̍��W�ɍ��킹��
            ColUpdate();
        }
    }

    if (tag == ObjectTag::Player)
    {
        if (abs(VSize(other->GetPos() - objPos)) < 12.0f && !firstMove)
        {
            if (animType != SAD)
            {
                animType = SAD;
                gstAnim->StartAnim(animType);
            }
            nowMove = false;
            aimDir = VScale(VNorm(aimPos - objPos), 0.1f);
            ColUpdate();
        }
    }

}

        // @brief Ghost��]���� //

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