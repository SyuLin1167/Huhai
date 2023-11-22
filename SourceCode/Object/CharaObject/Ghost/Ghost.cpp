#include "Ghost.h"
#include"../Player/Player.h"
#include"../../MapObject/Light/FlashLight/FlashLight.h"

Ghost::Ghost()
    :GhostBase()
    , moveCount(7.0f)
    , isFirstMove(true)
    ,aimPos(VGet(0.0f, 0.0f, 0.0f))
    , lightHandle(-1)
    , holdPos(VGet(0.0f, 0.0f, 0.0f))
{
    aimDir = VGet(0.0f, 0.0f, 1.0f);
    objPos = VGet(0.0f, 0.0f, -45.0f);

    //�A�j���[�V�����ݒ�
    if (animType != SAD)
    {
        animType = SAD;
        ghostAnim->StartAnim(animType);
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
    ghostSound->StartSound(SoundTag::Escape, DX_PLAYTYPE_LOOP);
}

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

void Ghost::Update(float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    ghostAnim->AddAnimTime(deltaTime);

    //���f����]
    MATRIX rotMatY = MGetRotY(PI_DEGREE * (float)(DX_PI / PI_DEGREE));
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
            ghostAnim->StartAnim(animType);

            //���C�g�ݒu
            ObjManager::GetFirstObj(ObjTag::Light)->SetVisible(false);
            lightHandle = CreatePointLightHandle(objPos, LIGHT_RANGE, 0.0f, 0.0f, LIGHT_ATTEN2);
            SetLightDifColorHandle(lightHandle, LIGHT_COLOR);

            ghostSound->StartSound(SoundTag::GhostScream, DX_PLAYTYPE_BACK);
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
        aimPos = ObjManager::GetFirstObj(ObjTag::Player)->GetPos();
    }

    //���쒆�͖ڕW���W�Ɍ������Ĉړ�
    if (isMove)
    {
        VECTOR moveVec = aimPos - objPos;
        moveVec = VNorm(moveVec);
        objPos += moveVec * objSpeed * deltaTime;
        aimDir = moveVec;
        objPos.y = GHOST_MOVE_POS_Y;
    }
    MV1SetPosition(objHandle, objPos);                        //�|�W�V�����ݒ�

    //���C�g�X�V
    if (lightHandle)
    {
        SetLightPositionHandle(lightHandle, objPos + LIGHT_POS);
    }

    //�����蔻��X�V
    ColUpdate();

    //�T�E���h�X�V
    ghostSound->Doppler(SoundTag::GhostScream, objPos);
    ghostSound->Doppler(SoundTag::Escape, objPos);
}

void Ghost::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}

void Ghost::OnCollisionEnter(const ObjBase* other)
{
    ObjTag tag = other->GetTag();

    //�����ɂԂ������牟���߂�
    if (tag == ObjTag::Map)
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
    if (tag == ObjTag::Player)
    {
        if (abs(VSize(other->GetPos() - objPos)) < HIT_DISTANCE && !isFirstMove)
        {
            if (animType != SAD)
            {
                animType = SAD;
                ghostAnim->StartAnim(animType);
            }
            isMove = false;
            aimDir = VScale(VNorm(aimPos - objPos), 0.1f);
            ColUpdate();
        }
    }

}