#include "Play.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../ResultScene/Result.h"

// @brief PlayScene�R���X�g���N�^�[ //

Play::Play()
    :SceneBase()
{
    BgHandle = LoadGraph("../SourceCode/Assets/BackGround/Play.png");

    SetCameraNearFar(CameraNear, CameraFar);                      //�J�����̕`��͈͐ݒ�

    ObjManager::Init();

    player = new Player();
    ObjManager::Entry(player);

    enemy = new Enemy();
    ObjManager::Entry(enemy);
}

// @brief PlayScene�f�X�g���N�^�[ //

Play::~Play()
{
    if (BgHandle != -1)
    {
        DeleteGraph(BgHandle);
    }
}

// @biref PlayScene�X�V���� //

SceneBase* Play::Update(float deltaTime)
{

    ObjManager::Update(deltaTime);


    if (enemy != nullptr)                                              //�C���X�^���X�̒��g����łȂ����
    {
        //---�����蔻�苅�擾---//
        Sphere sEmy, sPly;
        sEmy = enemy->GetColSphere();                                  //�A�[�`���[�̓����蔻�苅�擾
        sPly = player->GetColSphere();                                    //�v���C���[�̓����蔻�苅�擾

        if (CollisionPair(sEmy, sPly))                      //���̓��m�̓����蔻��
        {
            enemy->SetAlive(false);                                //�������Ă����玀�S
        }
    }

    if (CheckHitKey(KEY_INPUT_R))
    {
        return new Result();
    }
    return this;
}

// @brief PlayScene�`�揈�� //

void Play::Draw()
{
    //---�n�ʃO���b�h��`��---//(�̂��ɃQ�[���I�u�W�F�N�g�Ɉڍs)
    for (int ix = 0; ix < DivideNum + 1; ix++)
    {
        p1 = VGet(ix * GridSpace - GridAllSize * 0.5f, 0.0f, -GridAllSize * 0.5f);
        p2 = VGet(ix * GridSpace - GridAllSize * 0.5f, 0.0f, GridAllSize * 0.5f);

        DrawLine3D(p1, p2, GetColor(0, 255, 0));
    }
    for (int iy = 0; iy < DivideNum + 1; iy++)
    {
        p1 = VGet(-GridAllSize * 0.5f, 0.0f, iy * GridSpace - GridAllSize * 0.5f);
        p2 = VGet(GridAllSize * 0.5f, 0.0f, iy * GridSpace - GridAllSize * 0.5f);

        DrawLine3D(p1, p2, GetColor(0, 255, 0));
    }//�`��I���


    ObjManager::Draw();

    DrawFormatString(0, 0, GetColor(255, 255, 255), "Play���:R��Result�V�[���ֈڍs");
}