#include "Play.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Enemy/Enemy.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Furniture/MapFur.h"
#include "../ResultScene/Result.h"
#include "../../Grid/Grid.h"

// @brief PlayScene�R���X�g���N�^�[ //

Play::Play()
    :SceneBase()
{
    BgHandle = LoadGraph("../Assets/BackGround/Play.png");

    ObjManager::Init();

    ////---�J��������---//
    ObjManager::Entry(new CameraFps);

    ////---�v���C���[����---//
    ObjManager::Entry(new Player);

    ////---�G�l�~�[����---//
    //ObjManager::Entry(new Enemy());

    ////---�}�b�v�𐶐�---//
    ObjManager::Entry(new Map(VGet(0, 0, 0)));

    ////---�Ƌ�𐶐�---//
    ObjManager::Entry(new MapFur(VGet(0, 0, 0)));

    ////---�h�A�𐶐�---//
    ObjManager::Entry(new Door(VGet(22, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(110, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(77, 0, 100), VGet(0, 90, 0)));

    ////---�C�X�𐶐�---//
    ObjManager::Entry(new Chair(VGet(66,0,0),VGet(0,-90,0)));

    ////---�Ɩ��𐶐�---//
    ObjManager::Entry(new Light(VGet(-10, 32, 0)));
    ObjManager::Entry(new Light(VGet(60, 32, 0),true));
    ObjManager::Entry(new Light(VGet(120, 32, 30),true));

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
        AssetManager::ReleaseAllAsset();            //�S�ẴA�Z�b�g�̊J��
        ObjManager::ReleaceAllObj();                //�S�ẴI�u�W�F�N�g�̊J��
        return new Result();                        //���U���g��ʂ�
    }

    return this;                                    //��Ƀv���C�V�[����Ԃ�
}

// @brief PlayScene�`�揈�� //

void Play::Draw()
{
    ObjManager::Draw();
    grid->DrawGrid(300, 30);
    //DrawFormatString(0, 0, GetColor(255, 255, 255), "Play���:R��Result�V�[���ֈڍs");
}