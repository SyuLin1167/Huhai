#include "GhostMoveGim.h"
#include"../../../MapObject/Light/NomalLight/NomalLight.h"
#include"../../Man/Man.h"

// @brief GhostMoveGim�R���X�g���N�^ //

GhostMoveGim::GhostMoveGim()
    :GhostBase()
    ,light(nullptr)
    ,move(false)
{
    objPos = { 120.0f,0.0f,65.0f };

    //---�����蔻�苅�ݒ�---//
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, -40);			//���[�J�����W
    colSphere.Radius = 15.0f;						//�����a
    colSphere.worldCenter = objPos;					//���[���h���W

    objSpeed = 22.0f;
}

// @brief GhostMoveGim�f�X�g���N�^ //

GhostMoveGim::~GhostMoveGim()
{
}

// @brief GhostMoveGim�X�V���� //

void GhostMoveGim::Update(float deltaTime)
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

// @brief GhostMoveGim�`�揈�� //

void GhostMoveGim::Draw()
{
    MV1DrawModel(objHandle);
}

// @brief GhostMoveGim�Փˎ����� //

void GhostMoveGim::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();
    if (tag == ObjectTag::Player)
    {
        if (CollisionPair(colSphere, other->GetColSphere()))
        {
            if (animType != RUN)
            {
                animType = RUN;
                gstAnim->StartAnim(animType);
                move = true;
                light = ObjManager::GetFirstObj(ObjectTag::Light);
                if (light)
                {
                    light->SetPos(VGet(-30, 32, 75));
                }
                ObjManager::Entry(new Man);
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
            isAlive = false;                       //�������Փˎ��̍��W�ɍ��킹��
            ColUpdate();
        }
    }
}
