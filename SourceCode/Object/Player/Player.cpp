#include "Player.h"

// @brief Player�R���X�g���N�^�[ //

Player::Player()
    :ObjectBase(ObjectTag::Player)
    , plyAnim(nullptr)
    , animType(IDLE)
    , UP{ 0,0,0 }
    , DOWN{ 0,0,0 }
    , RIGHT{ 0,0,0 }
    , LEFT{ 0,0,0 }
    , inputVec{ 0,0,0 }
    , inputVel{ 0,0,0 }
    , aimDir{ 0,0,0 }
    , inputKey(false)
    , nowRoted(false)
    , camFront{ 0,0,0 }
{
    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Player/PlayerModel.mv1");       //���f���ǂݍ���
    MV1SetScale(objHandle, objScale);                                         //���f���̃T�C�Y�ݒ�

    plyAnim = new Animation(objHandle);                                                     //�A�j���[�V�����̃C���X�^���X
    plyCol = new Collision();

    //---�A�j���[�V�����ǂݍ���---//
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Idle.mv1");              //�ҋ@:0
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Run.mv1");               //����:1
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Atack.mv1", false);      //�U��:2

    //---�A�j���[�V������ԃZ�b�g---//
    plyAnim->StartAnim(animType);                       //�ҋ@���[�V�����ŃA�j���[�V�����J�n
    objDir = VGet(0, 0, 1);                //��������

    //---�����蔻�苅�ݒ�---//
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 6, 0);			//���[�J�����W
    colSphere.Radius = 5.0f;						//�����a
    colSphere.worldCenter = objPos;					//���[���h���W

    //---�����蔻������ݒ�---//
    colLine = Collision::Line(VGet(0.0f, 2.0f,0.0f), VGet(0.0f, -3.0f, 0.0f));

}

// @brief Player�f�X�g���N�^�[ //

Player::~Player()
{
    
    delete plyAnim;                                 //�A�j���[�V�������
}

//@brief Player�X�V����//

void Player::Update(float deltaTime)
{
    ObjectBase* camFps = ObjManager::GetFirstObj(ObjectTag::Camera);

    plyAnim->AddAnimTime(deltaTime);                //���݂̃A�j���[�V�����Đ���i�߂�

    camFront = objPos - camFps->GetPos();               //�J�����̐��ʕ����̈ʒu�x�N�g�����v�Z
    camFront.y = 0;
    camFront = VNorm(camFront);               //�x�N�g���𐳋K��

    UP = camFront;                               //�J���������ɑO�i
    DOWN = VScale(UP, -1.0f);              //�J��������ɑO�i
    RIGHT = VCross(VGet(0, 1, 0), camFront);     //�J�����E�����ɑO�i
    LEFT = VScale(RIGHT, -1.0f);                    //�J����������

    Rotate();                                               //Player��]����
    Move(deltaTime);                                        //Player�ړ�����

    MV1SetPosition(objHandle, objPos);                              //�|�W�V�����Z�b�g

    //---���f����]����---//
    MATRIX RotMatY = MGetRotY(180.0f * (float)(DX_PI / 180.0f));    //���f�����]�s��
    VECTOR negativeVec = VTransform(objDir, RotMatY);               //���̃x�N�g��
    MV1SetRotationZYAxis(objHandle, negativeVec,
    VGet(0.0f, 1.0f, 0.0f), 0.0f);                                  //���f����]

    colSphere.Move(objPos);                                         //�����蔻��̈ړ�
    ColUpdate();
}

// @brief Player�`�揈�� //

void Player::Draw()
{
    MV1DrawModel(objHandle);                                        //���f���`��
    ColDraw();
    //---�����蔻��f�o�b�O�`��(��ŏ���)---//
    DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
}

// @brief Player�Փˎ����� //

void Player::OnCollisionEnter(const ObjectBase* other)
{
    ObjectTag tag = other->GetTag();

    if (tag == ObjectTag::Map)                                      //�}�b�v�ƂԂ�������
    {
        int colModel = other->GetColModel();                        //���f�������蔻��擾

        //---�}�b�v�Ƌ��E���s�̓����蔻��---//
        MV1_COLL_RESULT_POLY_DIM colInfo;                          //���f�������蔻����
        if (plyCol->CollisionPair(colSphere, colModel, colInfo))
        {
            VECTOR pushBack = plyCol->CalcSpherePushBackFromMesh(colSphere, colInfo);   //�����߂��ʎZ�o
            objPos += pushBack;                                                         //�����߂�
            MV1CollResultPolyDimTerminate(colInfo);                        //�����蔻������
            ColUpdate();
        }

        //---�}�b�v�Ƒ��������̓����蔻��---//
        MV1_COLL_RESULT_POLY colInfoLine;                           //���������蔻����
        if (plyCol->CollisionPair(colLine, colModel, colInfoLine))
        {
            objPos = colInfoLine.HitPosition;                       //�������Փˎ��̍��W�ɍ��킹��
            ColUpdate();
        }
    }
}

// @brief Player�ړ����� //

void Player::Move(float deltaTime)
{
    //---�L�[���͔��菈��---//
    inputKey = false;                               //�����͎��͓��͔����FALSE��

    if (CheckHitKey(KEY_INPUT_LEFT))                //���L�[����
    {
        inputVec += LEFT;                           //�x�N�g�����Z
        inputKey = true;                            //���͔����TRUE��
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))               //�E�L�[����
    {
        inputVec += RIGHT;
        inputKey = true;
    }
    if (CheckHitKey(KEY_INPUT_UP))                  //��L�[����
    {
        inputVec += UP;
        inputKey = true;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))                //���L�[����
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

        if (IsSameAngle(inputVec, objDir))                      //���ݕ��������͕����ƈقȂ��Ă�����
        {
            objDir = inputVec;                                          //���͕������擾
        }
        else
        {
            nowRoted = true;
            aimDir = inputVec;
        }

        inputVel = inputVec * objSpeed * deltaTime;                  //�ړ����x�ݒ�

        if (animType != RUN)                                        //�A�j���[�V���������郂�[�V�����łȂ����
        {
            animType = RUN;                                         //�A�j���[�V�����͑��郂�[�V����
            plyAnim->StartAnim(RUN);                                //���郂�[�V�����ŃA�j���[�V�����J�n
        }
    }
    else
    {
        inputVel *= 0.9f;                                           //���X�Ɍ���
        if (animType != IDLE)                                       //�A�j���[�V�������ҋ@���[�V�����łȂ����
        {
            animType = IDLE;                                        //�A�j���[�V�����͑ҋ@���[�V����
            plyAnim->StartAnim(IDLE);                               //�ҋ@���[�V�����ŃA�j���[�V�����J�n
        }
    }
    objPos += inputVel;                                             //�ړ�
}

// @brief Player��]���� //

void Player::Rotate()
{
    if (nowRoted)                           //���݉�]����������
    {
        if (IsSameAngle( objDir,aimDir))     //�ڕW�̊p�x�ɏ\���߂Â��Ă�����
        {
            objDir = aimDir;                        //�p�x��ڕW�̊p�x�ɂ���
            nowRoted = false;                       //��]��~
        }
        else
        {
            VECTOR rotDir = RotForAimY(objDir, aimDir, 10.0f);     //��]���̃x�N�g��

            VECTOR cross1 = VCross(objDir, aimDir);            //�v���C���[�̊p�x�ƖڕW�p�̊O��
            VECTOR cross2 = VCross(rotDir, aimDir);            //��]���̊p�x�ƖڕW�p�̊O��

            if (cross1.y * cross2.y < 0.0f)                     //��]���ڕW�p�x�𒴂�����
            {
                rotDir = aimDir;                                //��]���̊p�x��ڕW�̊p�x�ɐݒ�
                nowRoted = false;                               //��]��~
            }
            
            objDir = rotDir;                                    // �ڕW�p��10�x�߂Â����p�x
        }
    }
}