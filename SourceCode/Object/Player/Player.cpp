#include "Player.h"

// @brief Player�R���X�g���N�^�[ //

Player::Player()
    :ObjectBase(ObjectTag::Player)
    ,UP{0,0,0}
    ,DOWN{0,0,0}
    ,RIGHT{0,0,0}
    ,LEFT{0,0,0}
    , InputVec{0,0,0}
    , KeyInput(false)
    ,plyAnim(nullptr)
    , animType(IDLE)
    ,cameraPos{0,58,0}
    ,cameraFront{0,0,0}
    ,cameraRotSpeed(0.5f)
    ,cameraRad(-40.0f)
{
    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Player/PlayerModel.mv1");       //���f���ǂݍ���
    MV1SetScale(objHandle, VGet(0.1f, 0.1f, 0.1f));                                         //���f���̃T�C�Y�ݒ�

    plyAnim = new Animation(objHandle);                                                     //�A�j���[�V�����̃C���X�^���X

    //---�A�j���[�V�����ǂݍ���---//
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Idle.mv1");              //�ҋ@:0
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Run.mv1");               //����:1
    plyAnim->AddAnimation("../SourceCode/Assets/Player/PlayerModel_Atack.mv1", false);      //�U��:2

    //---�A�j���[�V������ԃZ�b�g---//
    animType = IDLE;                                //�A�j���[�V�����͑ҋ@���[�V����
    plyAnim->StartAnim(IDLE);                       //�ҋ@���[�V�����ŃA�j���[�V�����J�n
    objDir = VGet(0.0f, 0.0f, 1.0f);                //��������
    objSpeed = 5.0f;                                //�������x

    //---�����蔻�苅�ݒ�---//
    colSphere.localCenter = VGet(0, 10, 0);			//���[�J�����W
    colSphere.Radius = 5.0f;						//�����a
    colSphere.worldCenter = objPos;					//���[���h���W
}

// @brief Player�f�X�g���N�^�[ //

Player::~Player()
{
    delete plyAnim;                                 //�A�j���[�V�������
}

//@brief Player�X�V����//

void Player::Update(float deltaTime)
{
    CameraUpdate(deltaTime);                        //�J�����X�V

    plyAnim->AddAnimTime(deltaTime);                //���݂̃A�j���[�V�����Đ���i�߂�

    cameraFront = objPos - cameraPos;               //�J�����̐��ʕ����̈ʒu�x�N�g�����v�Z
    cameraFront = VNorm(cameraFront);               //�x�N�g���𐳋K��

    UP = cameraFront;
    DOWN = VScale(cameraFront, -1.0f);
    RIGHT = VCross(VGet(0, 1, 0), cameraFront);
    LEFT = VScale(RIGHT, -1.0f);

    //---�L�[���͔��菈��---//
    KeyInput = false;                               //�����͎��͓��͔����FALSE��

    if (CheckHitKey(KEY_INPUT_LEFT))                //���L�[����
    {
        InputVec += LEFT;                           //�x�N�g�����Z
        KeyInput = true;                            //���͔����TRUE��
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))               //�E�L�[����
    {
        InputVec += RIGHT;
        KeyInput = true;
    }
    if (CheckHitKey(KEY_INPUT_UP))                  //��L�[����
    {
        InputVec += UP;
        KeyInput = true;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))                //���L�[����
    {
        InputVec += DOWN;
        KeyInput = true;
    }


    //---�ړ�����---//
    if (KeyInput)                                                   //�ړ��L�[�����͂��ꂽ��
    {
        InputVec = VNorm(InputVec);                                 //�x�N�g���̕����������擾
        objDir = InputVec;                                          //�L�����̌������擾
        objPos += InputVec * objSpeed * deltaTime;                  //�ړ�

        if (animType != RUN)                                        //�A�j���[�V���������郂�[�V�����łȂ����
        {
            animType = RUN;                                         //�A�j���[�V�����͑��郂�[�V����
            plyAnim->StartAnim(RUN);                                //���郂�[�V�����ŃA�j���[�V�����J�n
        }
    }
    else
    {
        if (animType != IDLE)                                       //�A�j���[�V�������ҋ@���[�V�����łȂ����
        {
            animType = IDLE;                                        //�A�j���[�V�����͑ҋ@���[�V����
            plyAnim->StartAnim(IDLE);                               //�ҋ@���[�V�����ŃA�j���[�V�����J�n
        }
    }
    MV1SetPosition(objHandle, objPos);                              //�|�W�V�����Z�b�g

    //---���f����]����---//
    MATRIX RotMatY = MGetRotY(180.0f * (float)(DX_PI / 180.0f));    //���f�����]�s��
    VECTOR negativeVec = VTransform(objDir, RotMatY);               //���̃x�N�g��
    MV1SetRotationZYAxis(objHandle, negativeVec,
    VGet(0.0f, 1.0f, 0.0f), 0.0f);                                  //���f����]

    colSphere.Move(objPos);                                         //�����蔻��̈ړ�
}

// @brief Player�`�揈�� //

void Player::Draw()
{
    MV1DrawModel(objHandle);                                        //���f���`��

    //---�����蔻��f�o�b�O�`��(��ŏ���)---//
    DrawSphere3D(colSphere.worldCenter, colSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
}

// @brief Camera�X�V���� //

void Player::CameraUpdate(float deltaTime)
{
    if (CheckHitKey(KEY_INPUT_Q))                                   //Q�L�[�������ꂽ��
    {
        cameraYaw -= cameraRotSpeed * deltaTime;                    //��]�p�͕��̕���
    }
    else if (CheckHitKey(KEY_INPUT_E))                              //E�L�[�������ꂽ��
    {
        cameraYaw += cameraRotSpeed * deltaTime;                    //��]�p�͐��̕���
    }
    cameraPos.x = cameraRad * cosf(cameraYaw);                      //�J������X�����W
    cameraPos.z = cameraRad * sinf(cameraYaw);                      //�J������Z�����W

    SetCameraPositionAndTarget_UpVecY(objPos + cameraPos,
        objPos + VGet(0, 8, 0));                                   //(0,8,0)�̎��_����v���C���[������p�x�ɃJ�����ݒu
}