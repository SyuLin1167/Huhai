#include "Room.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/MapObject/Map/Map.h"
#include"../../Object/MapObject/Bed/Bed.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include"../../UI/Action/Action.h"
#include"../../UI/Reamarks/Remarks.h"
#include"../PlayScene/Play.h"

// @brief Room�R���X�g���N�^ //

Room::Room()
    :SceneBase()
    , roomBlend(nullptr)
{
    //---�J��������---//
    ObjManager::Entry(new CameraFps);

    //---�}�b�v����---//
    ObjManager::Entry(new Map(Map::MapName::ROOM));

    //---�Ƌ�𐶐�---//
    ObjManager::Entry(new Furniture(Furniture::FurName::Room));

    //---�x�b�h�𐶐�---//
    ObjManager::Entry(new Bed);

    //---�v���C���[����---//
    ObjManager::Entry(new Player);

    //---�Ɩ��𐶐�---//
    ObjManager::Entry(new NomalLight(VGet(40, 32, 0)));

    ObjManager::Entry(new Remarks(TextType::OpeningText));

    roomBlend = new BlendMode;
}

// @brief Room�f�X�g���N�^ //

Room::~Room()
{

}

// @brief Room�X�V���� //

SceneBase* Room::Update(float deltaTime)
{
    ObjManager::Update(deltaTime);
    ObjManager::Collision();

    ObjectBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (!action->IsVisible())                               //�q�L�[�������ꂽ��
    {
        roomBlend->AddFade();
        if (!roomBlend->NowFade())
        {
            AssetManager::ReleaseAllAsset();            //�S�ẴA�Z�b�g�̊J��
            ObjManager::ReleaseAllObj();                //�S�ẴI�u�W�F�N�g�̊J��
            return new Play();                        //���U���g��ʂ�
        }
    }
	return this;
}

// @brief Room�`�揈�� //

void Room::Draw()
{
    ObjManager::Draw();
    DrawFormatString(0, 0, GetColor(255, 255, 255), "R���:P��Play�V�[���ֈڍs");
    roomBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    roomBlend->NoBlend();
}