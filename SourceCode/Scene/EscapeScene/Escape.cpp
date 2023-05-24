#include "Escape.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include"../../Object/MapObject/Table/Table.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/FlashLight/FlashLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../ResultScene/Result.h"

// @brief EscapeScene�R���X�g���N�^ //

EscapeScene::EscapeScene()
	:SceneBase()
{
    //---�J��������---//
    ObjManager::Entry(new CameraFps);

    //---�}�b�v�𐶐�---//
    ObjManager::Entry(new Map(Map::MapName::ESCAPE));
    ObjManager::Entry(new Map(Map::MapName::ESCAPEMAIN));

    //---�h�A�𐶐�---//
    ObjManager::Entry(new Door(VGet(53, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(183, 0, 0), VGet(0, 180, 0)));

    for (int i = 0; i < TableNum; i++)
    {
        ObjManager::Entry(new Table(i));
    }

    //---�Ɩ��𐶐�---//
    ObjManager::Entry(new NomalLight(VGet(23, 32, 10)));
    ObjManager::Entry(new NomalLight(VGet(175, 32, -30)));
    ObjManager::Entry(new FlashLight());

    //---�v���C���[����---//
    ObjManager::Entry(new Player);


}

// @brief EscapeScene�f�X�g���N�^ //

EscapeScene::~EscapeScene()
{

}

// @brief EscapeScene�X�V���� //

SceneBase* EscapeScene::Update(float deltaTime)
{
    ObjManager::Update(deltaTime);
    ObjManager::Collision();

    return this;
}

// @brief EscapeScene�`�揈�� //

void EscapeScene::Draw()
{
    ObjManager::Draw();
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Escape���:Result�V�[���ֈڍs");
}