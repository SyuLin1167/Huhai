#include "Play.h"
#include"../../Object/Camera/CameraFps.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include"../../Map/Block/Block.h"
#include"../../Map/Map/Map.h"
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

    // �u���b�N�𐶐�
    ObjManager::Entry(new Block(VGet(60, 0, 0)));
    ObjManager::Entry(new Block(VGet(70, 0, 10)));
    ObjManager::Entry(new Block(VGet(90, 0, 30)));
    ObjManager::Entry(new Block(VGet(50, 0, 10)));
    ObjManager::Entry(new Block(VGet(90, 0, 20)));

    // �}�b�v�𐶐�
    ObjManager::Entry(new Map(VGet(0, -25, 0)));

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
    ObjManager::Collision();

    if (enemy != nullptr)                                       //�C���X�^���X�̒��g����łȂ����
    {
        //---�����蔻�苅�擾---//
        Collision::Sphere sEmy, sPly;
        sEmy = enemy->GetColSphere();               //�A�[�`���[�̓����蔻�苅�擾
        sPly = player->GetColSphere();              //�v���C���[�̓����蔻�苅�擾

        if (col->CollisionPair(sEmy, sPly))         //���̓��m�̓����蔻��
        {
            enemy->SetAlive(false);                 //�������Ă����玀�S
            ObjManager::Release(enemy);
        }
    }

    if (CheckHitKey(KEY_INPUT_R))                               //�q�L�[�������ꂽ��
    {
        ObjManager::ReleaceAllObj();                //�S�ẴI�u�W�F�N�g�̊J��
        AssetManager::ReleaseAllAsset();            //�S�ẴA�Z�b�g�̊J��
        return new Result();                        //���U���g��ʂ�
    }

    return this;                                    //��Ƀv���C�V�[����Ԃ�
}

// @brief PlayScene�`�揈�� //

void Play::Draw()
{


    ObjManager::Draw();

    grid->DrawGrid(300, 30);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Play���:R��Result�V�[���ֈڍs");
}