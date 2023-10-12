#include "Player.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Scene/PauseScene/PauseMenu/PauseMenu.h"
#include"../../../Asset/Sound/Sound.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
    :ObjBase(ObjTag::Player)
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

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
void Player::Update(float deltaTime)
{
    //�J�����̌����擾
    ObjBase* camFps = ObjManager::GetFirstObj(ObjTag::Camera);
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
    if (ObjManager::GetFirstObj(ObjTag::Remarks))
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

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
    //�����Ȃ�
}

/// <summary>
/// �����蔻�菈��
/// </summary>
/// <param name="other">:�I�u�W�F�N�g</param>
void Player::OnCollisionEnter(const ObjBase* other)
{
    ObjTag tag = other->GetTag();

    //�����ɂԂ������牟���߂�
    if (tag == ObjTag::Map ||
        tag == ObjTag::Furniture)
    {
        int mapColModel = other->GetColModel();
        CollHitSphere(mapColModel);
        ColHitLine(mapColModel);
    }

    //�H��ɂԂ������玀�S
    if (tag == ObjTag::Ghost)
    {
        if (abs(VSize(other->GetPos() - objPos)) < HIT_DISTANCE && canMove)
        {
            canMove = false;
            isVisible = false;
            ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
            if (camera)
            {
                camera->SetDir(other->GetPos() - camera->GetPos() + HIT_AIM_POS);
            }
        }
        ColUpdate();
    }
}

/// <summary>
/// ���̂̏Փˎ�����
/// </summary>
/// <param name="colmodel">:�����蔻�胂�f��</param>
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

/// <summary>
/// �����̏Փˎ�����
/// </summary>
/// <param name="colmodel">:�����蔻�胂�f��</param>
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

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
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