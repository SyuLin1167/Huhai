#include "GhostWalkGim.h"

#include"../../../MapObject/Light/NomalLight/NomalLight.h"
#include"../../../MapObject/Door/Door.h"
#include"../../Man/Man.h"

GhostWalkGim::GhostWalkGim()
    :GhostBase()
{
    objPos = VGet(120.0f, 0.0f, 65.0f);
    objSpeed = 17.0f;

    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, -40);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;
}

GhostWalkGim::~GhostWalkGim()
{
    //�����Ȃ�
}

void GhostWalkGim::Update(const float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    ghostAnim->AddAnimTime(deltaTime);

    //���쒆�͈ړ�
    if (isMove)
    {
        //�����蔻��ݒ�
        ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
        colLine = Line(COL_LINE_FIRST_POS+COL_LINE_HEIGHT,
            player->GetPos() - objPos + COL_LINE_HEIGHT);

        objPos.x -= objSpeed * deltaTime;
    }

    //���f����]
    MV1SetPosition(objHandle, objPos);
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);

    //�����蔻��X�V
    ColUpdate();
}

void GhostWalkGim::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}

void GhostWalkGim::OnCollisionEnter(const ObjBase* other)
{
    ObjTag tag = other->GetTag();

    //�v���C���[����苗���߂Â����瓮��J�n
    if (tag == ObjTag::Player)
    {
        if (CollisionPair(colSphere, other->GetColSphere()))
        {
            //�H����������
            if (animType != WALK)
            {
                animType = WALK;
                ghostAnim->StartAnim(animType);
                ghostSound->StartSound(SoundTag::GhostWalk, DX_PLAYTYPE_BACK);
                isMove = true;
            }
        }
    }

    //���g�ƃv���C���[�Ԃ̐����������ɂԂ������玀�S����
    if (tag == ObjTag::Map ||
        tag == ObjTag::Furniture)
    {
        int mapColModel = other->GetColModel();
        MV1_COLL_RESULT_POLY colInfoLine;
        if (CollisionPair(colLine, mapColModel, colInfoLine))
        {
            isVisible = false;
            if (!ghostSound->IsPlaying(SoundTag::GhostWalk))
            {
                isAlive = false;
            }
            ColUpdate();
        }
    }
}