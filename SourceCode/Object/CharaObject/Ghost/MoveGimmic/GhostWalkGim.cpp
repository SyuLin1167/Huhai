#include "GhostWalkGim.h"

#include"../../../MapObject/Light/NomalLight/NomalLight.h"
#include"../../../MapObject/Door/Door.h"
#include"../../Man/Man.h"

// �R���X�g���N�^ //

GhostWalkGim::GhostWalkGim()
    :GhostBase()
    , isMove(false)
{
    objPos = VGet(120.0f, 0.0f, 65.0f);
    objSpeed = 17.0f;

    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, -40);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;
}

// �f�X�g���N�^ //

GhostWalkGim::~GhostWalkGim()
{
}

// �X�V���� //

void GhostWalkGim::Update(float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    gstAnim->AddAnimTime(deltaTime);

    //���쒆�͈ړ�
    if (isMove)
    {
        //�����蔻��ݒ�
        ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
        colLine = Line(VGet(7.0f, 5.0f, 0.0f), player->GetPos() - objPos + VGet(0, 5, 0));             //�����ݒ�

        objPos.x -= objSpeed * deltaTime;
    }

    //���f����]
    MV1SetPosition(objHandle, objPos);
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);

    //�����蔻��X�V
    ColUpdate();
}

// �`�揈�� //

void GhostWalkGim::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}

// �Փˎ����� //

void GhostWalkGim::OnCollisionEnter(const ObjBase* other)
{
    ObjectTag tag = other->GetTag();

    //�v���C���[����苗���߂Â����瓮��J�n
    if (tag == ObjectTag::Player)
    {
        if (CollisionPair(colSphere, other->GetColSphere()))
        {
            //�H����������
            if (animType != WALK)
            {
                animType = WALK;
                gstAnim->StartAnim(animType);
                gstSound->StartSound(SoundTag::GhostWalk, DX_PLAYTYPE_BACK);
                isMove = true;

                //���C�g�̈ʒu�ύX
                ObjBase* light = ObjManager::GetFirstObj(ObjectTag::Light);
                if (light)
                {
                    light->SetPos(VGet(-32, 33, 75));
                }

                ////�h�A�ǉ�(�J������)
                //class Door* door = new Door(VGet(0, 0, 66), VGet(-1, 0, 0));
                //ObjManager::Entry(door);
                //door->MoveAnim(Door::AnimType::OPEN);
            }
        }
    }

    //���g�ƃv���C���[�Ԃ̐����������ɂԂ������玀�S����
    if (tag == ObjectTag::Map ||
        tag == ObjectTag::Furniture)
    {
        int mapColModel = other->GetColModel();
        MV1_COLL_RESULT_POLY colInfoLine;
        if (CollisionPair(colLine, mapColModel, colInfoLine))
        {
            isVisible = false;
            if (!gstSound->IsPlaying(SoundTag::GhostWalk))
            {
                isAlive = false;
            }
            ColUpdate();
        }
    }
}