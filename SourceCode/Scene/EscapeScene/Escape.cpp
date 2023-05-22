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

// @brief EscapeSceneコンストラクタ //

EscapeScene::EscapeScene()
	:SceneBase()
{
    ////---カメラ生成---//
    ObjManager::Entry(new CameraFps);

    ////---マップを生成---//
    ObjManager::Entry(new Map(Map::MapName::ESCAPE));
    ObjManager::Entry(new Map(Map::MapName::ESCAPEMAIN));

    ////---家具を生成---//
    ObjManager::Entry(new Furniture(Furniture::FurName::Stage));

    ////---ドアを生成---//
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));

    ////---照明を生成---//
    ObjManager::Entry(new NomalLight(VGet(-10, 32, 0)));
    ObjManager::Entry(new LitLight(VGet(65, 32, 0), 50.0f));
    ObjManager::Entry(new LitLight(VGet(120, 32, 20), 40.0f));

    ////---プレイヤー生成---//
    ObjManager::Entry(new Player);

    ////---エネミー生成---//
    ObjManager::Entry(new GhostWalkGim);

    ObjManager::Entry(new Remarks(TextType::Day1Stage));
}

// @brief EscapeSceneデストラクタ //

EscapeScene::~EscapeScene()
{

}

// @brief EscapeScene更新処理 //

SceneBase* EscapeScene::Update(float deltaTime)
{
    ObjManager::Update(deltaTime);
    ObjManager::Collision();

    return this;
}

// @brief EscapeScene描画処理 //

void EscapeScene::Draw()
{
    ObjManager::Draw();
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Escape画面:Resultシーンへ移行");
}