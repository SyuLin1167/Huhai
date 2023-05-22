#include "Play.h"

#include"../EscapeScene/Escape.h"
#include"../ResultScene/Result.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/MoveGimmic/GhostWalkGim.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/LightingLight/LitLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../UI/Reamarks/Remarks.h"

// @brief PlayScene�R���X�g���N�^ //

Play::Play()
    :SceneBase()
    ,sceneChange(false)
{
    ////---�J��������---//
    ObjManager::Entry(new CameraFps);

    ////---�}�b�v�𐶐�---//
    ObjManager::Entry(new Map(Map::MapName::STAGE));

    ////---�Ƌ�𐶐�---//
    ObjManager::Entry(new Furniture(Furniture::FurName::Stage));

    ////---�h�A�𐶐�---//
    ObjManager::Entry(new Door(VGet(22, 0, 0), VGet(0, 180, 0)));
    ObjManager::Entry(new Door(VGet(110, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));

    ////---�C�X�𐶐�---//
    ObjManager::Entry(new Chair);

    ////---�Ɩ��𐶐�---//
    ObjManager::Entry(new NomalLight(VGet(-10, 32, 0)));
    ObjManager::Entry(new LitLight(VGet(65, 32, 0),50.0f));
    ObjManager::Entry(new LitLight(VGet(120, 32, 20),40.0f));

    ////---�v���C���[����---//
    ObjManager::Entry(new Player);

    ////---�G�l�~�[����---//
    ObjManager::Entry(new GhostWalkGim);

    ObjManager::Entry(new Remarks(TextType::Day1Stage));
}

// @brief PlayScene�f�X�g���N�^ //

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


    ObjectBase* man = ObjManager::GetFirstObj(ObjectTag::Man);
    if (man)                               //�q�L�[�������ꂽ��
    {
            sceneChange = true;
    }
    else if (sceneChange)
    {
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();
        return new EscapeScene;                        //���U���g��ʂ�
    }

    return this;                                    //��Ƀv���C�V�[����Ԃ�
}

// @brief PlayScene�`�揈�� //

void Play::Draw()
{
    ObjManager::Draw();
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Stage���:Escape�V�[���ֈڍs");
}