#include "Player.h"

// @brief Player�R���X�g���N�^�[ //

Player::Player()
    :ObjectBase(ObjectTag::Player)
    , inputVec{ 0,0,0 }
    , UP{ 0,0,0 }
    , DOWN{ 0,0,0 }
    , LEFT{ 0,0,0 }
    , RIGHT{ 0,0,0 }
    , inputVel{ 0,0,0 }
    , inputKey(false)
    , nowRoted(false)
    , camFront{ 0,0,0 }
{

    //---�C���X�^���X---//

    objPos = { 0,0,0 };

    //---�����蔻�苅�ݒ�---//
    colType = CollisionType::Sphere;                                                        //�����蔻��͋���
    colSphere.localCenter = VGet(0, 5, 0);                                                  //���[�J�����W
    colSphere.Radius = 3.0f;                                                                //�����a
    colSphere.worldCenter = objPos;                                                         //���[���h���W

    //---�����蔻������ݒ�---//
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -3.0f, 0.0f));             //�����ݒ�

}

// @brief Player�f�X�g���N�^�[ //

Player::~Player()
{

}

//@brief Player�X�V����//

void Player::Update(float deltaTime)
{
    ObjectBase* camFps = ObjManager::GetFirstObj(ObjectTag::Camera);
    camFront = camFps->GetDir();               //�J�����̐��ʕ����̈ʒu�x�N�g�����v�Z
    camFront.y = 0;
    camFront = VNorm(camFront);               //�x�N�g���𐳋K��

    UP = camFront;                               //�J���������ɑO�i
    DOWN = VScale(UP, -1.0f);              //�J�������������i
    RIGHT = VCross(VGet(0, 1, 0), camFront);     //�J������������E�ɑO�i
    LEFT = VScale(RIGHT, -1.0f);                    //�J�����������獶�ɑO�i

    objDir = camFront;
    Move(deltaTime);                                        //Player�ړ�����

    objPos.y = 0;
    MV1SetPosition(objHandle, objPos);                              //�|�W�V�����Z�b�g

    colSphere.Move(objPos);                                         //�����蔻��̈ړ�
    ColUpdate();
}

// @brief Player�`�揈�� //

void Player::Draw()
{
    ColDraw();
}

// @brief Player�Փˎ����� //

void Player::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();

    if (tag == ObjectTag::Map||
        tag == ObjectTag::Furniture)                                      //�}�b�v�ƂԂ�������
    {
        int mapColModel = other->GetColModel();                        //���f�������蔻��擾
        CollHitSphere(mapColModel);
        ColHitLine(mapColModel);
    }
}

// @brief ���̂̏Փˎ����� //

void Player::CollHitSphere(int colmodel)
{
    //---�}�b�v�Ƌ��E���Ƃ̓����蔻��---//
    MV1_COLL_RESULT_POLY_DIM colInfo;                          //���f�������蔻����
    if (CollisionPair(colSphere, colmodel, colInfo))
    {
        VECTOR pushBack = CalcSpherePushBackFromMesh(colSphere, colInfo);   //�����߂��ʎZ�o
        objPos += pushBack;                                                         //�����߂�
        MV1CollResultPolyDimTerminate(colInfo);                        //�����蔻������
        ColUpdate();
    }

}

// @brief �����̏Փˎ����� //

void Player::ColHitLine(int colmodel)
{
    //---�}�b�v�Ƒ��������̓����蔻��---//
    MV1_COLL_RESULT_POLY colInfoLine;                           //���������蔻����
    if (CollisionPair(colLine, colmodel, colInfoLine))
    {
        objPos = colInfoLine.HitPosition;                       //�������Փˎ��̍��W�ɍ��킹��
        ColUpdate();
    }
}

// @brief Player�ړ����� //

void Player::Move(float deltaTime)
{
    //---�L�[���͔��菈��---//
    inputKey = false;                               //�����͎��͓��͔����FALSE��

    if (CheckHitKey(KEY_INPUT_A))                //���L�[����
    {
        inputVec += LEFT;                           //�x�N�g�����Z
        inputKey = true;                            //���͔����TRUE��
    }
    if (CheckHitKey(KEY_INPUT_D))               //�E�L�[����
    {
        inputVec += RIGHT;
        inputKey = true;
    }
    if (CheckHitKey(KEY_INPUT_W))                  //��L�[����
    {
        inputVec += UP;
        inputKey = true;
    }
    if (CheckHitKey(KEY_INPUT_S))                //���L�[����
    {
        inputVec += DOWN;
        inputKey = true;
    }


    //---�ړ�����---//
    if (inputKey)                                                   //�ړ��L�[�����͂��ꂽ��
    {

        inputVec = VNorm(inputVec);                                 //�x�N�g���̕����������擾
        
        if (VSquareSize(inputVec)==0)                               //���E�E�㉺���������̍ۂ͖���
        {
            return;
        }

        inputVel = inputVec * objSpeed * deltaTime;                  //�ړ����x�ݒ�
    }
    else
    {
        inputVel *= 0.5f;                                           //���X�Ɍ���
    }
    objPos += inputVel;                                             //�ړ�
}
