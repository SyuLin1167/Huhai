#include "Enemy.h"


/* @brief Enemy�R���X�g���N�^ */

Enemy::Enemy()
    :ObjectBase(ObjectTag::Enemy)
{
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Enemy/SampleEnemy.MV1");        //���f���ǂݍ���
    MV1SetScale(objHandle, VGet(0.1f, 0.1f, 0.1f));                             //���f���̃T�C�Y�ݒ�
    objDir = VGet(-1.0f, 0.0f, 0.0f);                                           //��������
    objPos = VGet(10.0f, 0.0f, 0.0f);                                           //�����ʒu
    MV1SetPosition(objHandle, objPos);                                          //�|�W�V�����ݒ�

    objSpeed = 5.0f;

    //---�����蔻�苅�ݒ�---//
    colSphere.localCenter = VGet(0, 10, 0);			//���[�J�����W
    colSphere.Radius = 5.0f;						//�����a
    colSphere.worldCenter = objPos;					//���[���h���W
}

// @brief Enemy�f�X�g���N�^�[ //

Enemy::~Enemy()
{
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
}

// @brief Enemy�X�V���� //

void Enemy::Update(float deltaTime)
{
    objPos += objDir * objSpeed * deltaTime;                //�ړ�
    MV1SetPosition(objHandle, objPos);                        //�|�W�V�����ݒ�
    MATRIX RotMatY = MGetRotY(90 * (float)(DX_PI / 90.0f));       //�������ɉ�]������
    MV1SetRotationZYAxis(objHandle, VTransform(objDir, RotMatY), VGet(0.0f, 1.0f, 0.0f), 0.0f);         //���f����]

    colSphere.Move(objPos);					//�����蔻��̈ړ�
}

// @brief Enemy�`�揈�� //

void Enemy::Draw()
{
    MV1DrawModel(objHandle);


    //---�����蔻��f�o�b�O�`��(��ŏ���)---//
    DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
}

