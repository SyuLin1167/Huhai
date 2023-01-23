#include "Play.h"
#include"../../Object/Camera/CameraFps.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include"../../Map/Map/Map.h"
#include"../../Map/Door/Door.h"
#include"../../Map/Furniture/Furniture.h"
#include "../ResultScene/Result.h"
#include"../../Grid/Grid.h"

// @brief PlayScene�R���X�g���N�^�[ //

Play::Play()
    :SceneBase()
{
    BgHandle = LoadGraph("../SourceCode/Assets/BackGround/Play.png");

    ObjManager::Init();

    //---�J��������---//
    ObjManager::Entry(new CameraFps());

    //---�v���C���[����---//
    ObjManager::Entry(new Player());

    //---�G�l�~�[����---//
    ObjManager::Entry(new Enemy());

    //---�}�b�v�𐶐�---//
    ObjManager::Entry(new Map(VGet(0, 0, 0)));

    //---�h�A�𐶐�---//
    ObjManager::Entry(new Door(VGet(20, 0, 0),VGet(0,0,0)));
    ObjManager::Entry(new Door(VGet(100, 0, 0),VGet(0,0,0)));
    ObjManager::Entry(new Door(VGet(0, 0, 60), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(70, 0, 90), VGet(0, 90, 0)));
    
    //---�Ƌ�𐶐�---//
    ObjManager::Entry(new Furniture(VGet(0, 0, 0)));

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

    //grid->DrawGrid(300, 30);
    //DrawFormatString(0, 0, GetColor(255, 255, 255), "Play���:R��Result�V�[���ֈڍs");
}