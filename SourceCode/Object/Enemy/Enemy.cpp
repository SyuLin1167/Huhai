#include "Enemy.h"


/* @brief Enemy�R���X�g���N�^ */

Enemy::Enemy()
    :ObjectBase(ObjectTag::Enemy)
    ,emyAnim(nullptr)
    ,animType(IDLE)
{
    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Enemy/unityChanModel.mv1");        //���f���ǂݍ���
    MV1SetScale(objHandle, VGet(0.01f, 0.01f, 0.01f));                             //���f���̃T�C�Y�ݒ�
    
    emyAnim = new Animation(objHandle);                                         //�A�j���[�V�����̃C���X�^���X
   
    //---�A�j���[�V�����ǂݍ���---//
    emyAnim->AddAnimation("../SourceCode/Assets/Enemy/unityChanAnimIdle.mv1");      //�ҋ@:0
    emyAnim->AddAnimation("../SourceCode/Assets/Enemy/unityChanAnimRun.mv1");       //����:1
    emyAnim->AddAnimation("../SourceCode/Assets/Enemy/unityChanAnimPunch.mv1");     //�U��:2

    //---�A�j���[�V������ԃZ�b�g---//
    emyAnim->StartAnim(animType);
    objDir = VGet(-1.0f, 0.0f, 0.0f);                                           //��������
    objPos = VGet(50.0f, 0.0f, 0.0f);                                           //�����ʒu
    MV1SetPosition(objHandle, objPos);                                          //�|�W�V�����ݒ�

    //---�����蔻�苅�ݒ�---//
    colSphere.localCenter = VGet(0, 10, 0);			//���[�J�����W
    colSphere.Radius = 5.0f;						//�����a
    colSphere.worldCenter = objPos;					//���[���h���W

    objSpeed = 5.0f;
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
    Move(deltaTime);
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

void Enemy::Move(float deltaTime)
{
    objPos += objDir * objSpeed * deltaTime;                //�ړ�
    if (animType != RUN)
    {
        animType = RUN;
        emyAnim->StartAnim(animType);
    }
}