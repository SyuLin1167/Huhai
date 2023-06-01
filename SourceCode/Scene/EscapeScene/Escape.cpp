#include "Escape.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include"../../Object/CharaObject/Ghost/Ghost.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include"../../Object/MapObject/Table/Table.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/FlashLight/FlashLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include"../../BlendMode/BlendMode.h"
#include "../ResultScene/Result.h"
#include"../TitleScene/Title.h"

// @brief EscapeScene�R���X�g���N�^ //

EscapeScene::EscapeScene()
	:SceneBase()
{
    //---�J��������---//
    ObjManager::Entry(new CameraFps);

    //---�}�b�v�𐶐�---//
    ObjManager::Entry(new Map(Map::MapName::ESCAPE));
    ObjManager::Entry(new Map(Map::MapName::ESCAPEMAIN));
    ObjManager::Entry(new Map(Map::MapName::GOAL));

    //---�h�A�𐶐�---//
    ObjManager::Entry(new Door(VGet(55, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(187, 0, 0), VGet(0, 180, 0)));
    ObjManager::Entry(new Door(VGet(759, 0, 0), VGet(0, 180, 0)));

    //---���𐶐�---//
    for (int i = 0; i < TableNum; i++)
    {
        ObjManager::Entry(new Table(i));
    }

    //---�Ɩ��𐶐�---//
    ObjManager::Entry(new BlinkingLight(VGet(23, 32, 10)));
    ObjManager::Entry(new NomalLight(VGet(175, 32, -30)));
    ObjManager::Entry(new FlashLight());

    //---�v���C���[����---//
    ObjManager::Entry(new Player);

    ObjManager::Entry(new Ghost);

    escBlend = new BlendMode(2);
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

    if (!ObjManager::GetObj(ObjectTag::Map, 2))
    {
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();
        return new Result;
    }
    else if (!ObjManager::GetFirstObj(ObjectTag::Player)->IsVisible())
    {
        escBlend->AddFade();
        if (!escBlend->NowFade())
        {
            AssetManager::ReleaseAllAsset();
            ObjManager::ReleaseAllObj();
            return new Title;
        }
    }
    return this;
}

// @brief EscapeScene�`�揈�� //

void EscapeScene::Draw()
{
    ObjManager::Draw();
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Escape���:Result�V�[���ֈڍs");
    escBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    escBlend->NoBlend();
}