#include "Ghost.h"
#include"../Player/Player.h"

/* @brief Ghost�R���X�g���N�^ */

Ghost::Ghost()
    :GhostBase()
{
    //---�����蔻�苅�ݒ�---//
    colSphere.localCenter = VGet(0, 10, 0);			//���[�J�����W
    colSphere.Radius = 5.0f;						//�����a
    colSphere.worldCenter = objPos;					//���[���h���W

    objSpeed = 5.0f;
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

    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);



    MV1SetPosition(objHandle, objPos);                        //�|�W�V�����ݒ�
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));       //�������ɉ�]������
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);         //���f����]

    
    colSphere.Move(objPos);					//�����蔻��̈ړ�
}

// @brief Ghost�`�揈�� //

void Ghost::Draw()
{
    MV1DrawModel(objHandle);

    ////---�����蔻��f�o�b�O�`��(��ŏ���)---//
    //DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
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

}
