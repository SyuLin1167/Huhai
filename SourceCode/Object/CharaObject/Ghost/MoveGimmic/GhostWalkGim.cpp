#include "GhostWalkGim.h"
#include"../../../MapObject/Light/NomalLight/NomalLight.h"
#include"../../Man/Man.h"

// @brief GhostWalkGim�R���X�g���N�^ //

GhostWalkGim::GhostWalkGim()
    :GhostBase()
    ,light(nullptr)
    ,move(false)
{
    objPos = VGet(120.0f, 0.0f, 65.0f);

    //---�����蔻�苅�ݒ�---//
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, -40);			//���[�J�����W
    colSphere.Radius = 15.0f;						//�����a
    colSphere.worldCenter = objPos;					//���[���h���W

    objSpeed = 17.0f;
}

// @brief GhostWalkGim�f�X�g���N�^ //

GhostWalkGim::~GhostWalkGim()
{
}

// @brief GhostWalkGim�X�V���� //

void GhostWalkGim::Update(float deltaTime)
{
    gstAnim->AddAnimTime(deltaTime);
    if (move)
    {
        //---�����蔻������ݒ�---//
        ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
        colLine = Line(VGet(7.0f, 5.0f, 0.0f), player->GetPos() - objPos+VGet(0,5,0));             //�����ݒ�

        objPos.x -= objSpeed * deltaTime;
    }

    MV1SetPosition(objHandle, objPos);                        //�|�W�V�����ݒ�
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));       //�������ɉ�]������
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);         //���f����]

    ColUpdate();
}

// @brief GhostWalkGim�`�揈�� //

void GhostWalkGim::Draw()
{
    MV1DrawModel(objHandle);
}

// @brief GhostWalkGim�Փˎ����� //

void GhostWalkGim::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();
    if (tag == ObjectTag::Player)
    {
        if (CollisionPair(colSphere, other->GetColSphere()))
        {
            if (animType != WALK)
            {
                animType = WALK;
                gstAnim->StartAnim(animType);
                gstSound->StartSound(SoundTag::GhostWalk, DX_PLAYTYPE_BACK);
                move = true;
                light = ObjManager::GetFirstObj(ObjectTag::Light);
                if (light)
                {
                    light->SetPos(VGet(-32, 32, 75));
                }
            }
        }
    }
    if (tag == ObjectTag::Map ||
        tag == ObjectTag::Furniture)                                      //�}�b�v�ƂԂ�������
    {
        int mapColModel = other->GetColModel();                        //���f�������蔻��擾
        //---�}�b�v�Ƒ��������̓����蔻��---//
        MV1_COLL_RESULT_POLY colInfoLine;                           //���������蔻����
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
