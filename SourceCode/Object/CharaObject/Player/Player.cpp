#include "Player.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Scene/PauseMenu/PauseMenu.h"
#include"../../../Asset/Sound/Sound.h"

// �R���X�g���N�^ //

Player::Player()
    :ObjBase(ObjectTag::Player)
    , canMove(true)
    , UP(VGet(0,0,0))
    , DOWN(VGet(0,0,0))
    , LEFT(VGet(0,0,0))
    , RIGHT(VGet(0,0,0))
    , inputVec(VGet(0,0,0))
    , inputVel(VGet(0,0,0))
    , walkStep(0.0f)
    , inputKey(false)
    , camFront(VGet(0,0,0))
    , plySound(nullptr)
{
    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5.0f, 0);
    colSphere.Radius = 3.0f;
    colSphere.worldCenter = objPos;
    colLine = Line(VGet(0.0f, 2.0f, 0.0f), VGet(0.0f, -3.0f, 0.0f));

    //�T�E���h�ݒ�
    plySound = new Sound;
    plySound->AddSound("../Assets/Sound/PlayerWalkSE.mp3", SoundTag::PlayerWalk, false, true);
}

// �f�X�g���N�^ //

Player::~Player()
{
}

// �X�V���� //

void Player::Update(float deltaTime)
{
    //�J�����̌����擾
    ObjBase* camFps = ObjManager::GetFirstObj(ObjectTag::Camera);
    camFront = camFps->GetDir();
    camFront.y = 0;
    camFront = VNorm(camFront);

    //�ړ����̃J�����̏㉺�^��
    if (PauseMenu::HasStatus("Camera"))
    {
        if (inputKey)
        {
            if (walkStep < DX_PI_F)
            {
                walkStep += 5.0f * deltaTime;
            }
            else
            {
                walkStep = 0;
            }
            camFps->SetPos(VGet(objPos.x, camFps->GetPos().y + sin(walkStep), objPos.z));
        }
    }

    //�J�����̌����ɍ��킹�Ĉړ���������
    UP = camFront;
    DOWN = VScale(UP, -1.0f);
    RIGHT = VCross(VGet(0, 1, 0), camFront);
    LEFT = VScale(RIGHT, -1.0f);
    objDir = camFront;

    //���쒆�͑���\
    if (canMove)
    {
        Move(deltaTime);
    }

    //�Z���t�\�����͓����~
    if (ObjManager::GetFirstObj(ObjectTag::Remarks))
    {
        canMove = false;
    }
    else
    {
        canMove = true;
    }

    //�����蔻��X�V
    ColUpdate();
}

// �`�揈�� //

void Player::Draw()
{
}

// �Փˎ����� //

void Player::OnCollisionEnter(const ObjBase* other)
{
    ObjectTag tag = other->GetTag();

    //�����ɂԂ������牟���߂�
    if (tag == ObjectTag::Map ||
        tag == ObjectTag::Furniture)
    {
        int mapColModel = other->GetColModel();
        CollHitSphere(mapColModel);
        ColHitLine(mapColModel);
    }

    //�H��ɂԂ������玀�S
    if (tag == ObjectTag::Ghost)
    {
        if (abs(VSize(other->GetPos() - objPos)) < 12.0f && canMove)
        {
            canMove = false;
            isVisible = false;
            ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
            if (camera)
            {
                camera->SetDir(other->GetPos() - camera->GetPos() + VGet(0, 18.0f, 0));
            }
        }
        ColUpdate();
    }
}

// ���̂̏Փˎ����� //

void Player::CollHitSphere(int colmodel)
{
    //���̂����f���̓��������牟���߂�
    MV1_COLL_RESULT_POLY_DIM colInfo;
    if (CollisionPair(colSphere, colmodel, colInfo))
    {
        VECTOR pushBack = CalcSpherePushBackFromMesh(colSphere, colInfo);
        objPos += pushBack;
        MV1CollResultPolyDimTerminate(colInfo);
        ColUpdate();
    }

}

// �����̏Փˎ����� //

void Player::ColHitLine(int colmodel)
{
    //���������f���ɓ��������瑫���̍��W�ɍ��킹��
    MV1_COLL_RESULT_POLY colInfoLine;
    if (CollisionPair(colLine, colmodel, colInfoLine))
    {
        objPos = colInfoLine.HitPosition;
        ColUpdate();
    }
}

// �ړ����� //

void Player::Move(float deltaTime)
{
    //�ʏ�͖�����
    inputKey = false;

    //A�L�[���͂ō��Ɉړ�
    if (CheckHitKey(KEY_INPUT_A))
    {
        inputVec += LEFT;
        inputKey = true;
    }
    //D�L�[���͂ŉE�Ɉړ�
    if (CheckHitKey(KEY_INPUT_D))
    {
        inputVec += RIGHT;
        inputKey = true;
    }
    //W�L�[���͂őO�Ɉړ�
    if (CheckHitKey(KEY_INPUT_W))
    {
        inputVec += UP;
        inputKey = true;
    }
    //S�L�[���͂Ō��Ɉړ�
    if (CheckHitKey(KEY_INPUT_S))
    {
        inputVec += DOWN;
        inputKey = true;
    }

    //�L�[���͒��͈ړ�
    if (inputKey)
    {
        plySound->StartSound(SoundTag::PlayerWalk, DX_PLAYTYPE_LOOP);
        inputVec = VNorm(inputVec);
        if (VSquareSize(inputVec) == 0)
        {
            return;
        }
        inputVel = inputVec * objSpeed * deltaTime;
    }
    else
    {
        //�����͎��͈ړ���~
        plySound->StopSound(SoundTag::PlayerWalk);
        inputVel *= 0.0f;
    }
    objPos += inputVel;
}