#include "Escape.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/MoveGimmic/GhostWalkGim.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/LightingLight/LitLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include"../../UI/Reamarks/Remarks.h"
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
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));

    //---�Ɩ��𐶐�---//
    ObjManager::Entry(new NomalLight(VGet(23, 32, 10)));
    ObjManager::Entry(new NomalLight(VGet(170, 32, -15)));

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