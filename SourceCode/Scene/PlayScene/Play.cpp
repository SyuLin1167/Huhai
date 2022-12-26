#include "Play.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Object/Camera/CameraFps.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../ResultScene/Result.h"
#include"../../Grid/Grid.h"

// @brief PlayScene�R���X�g���N�^�[ //

Play::Play()
    :SceneBase()
{
    BgHandle = LoadGraph("../SourceCode/Assets/BackGround/Play.png");

    ObjManager::Init();

    camFps = new CameraFps();
    ObjManager::Entry(camFps);

    player = new Player();
    ObjManager::Entry(player);

    enemy = new Enemy();
    ObjManager::Entry(enemy);

    grid = new Grid;
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
        ObjManager::ReleaceAllObj();
        AssetManager::ReleaseAllAsset();
        return new Result();

    }
    return this;
}

// @brief PlayScene�`�揈�� //

void Play::Draw()
{


    ObjManager::Draw();

    grid->DrawGrid(300, 30);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Play���:R��Result�V�[���ֈڍs");
}