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
    //---カメラ生成---//
    ObjManager::Entry(new CameraFps);

    //---マップを生成---//
    ObjManager::Entry(new Map(Map::MapName::ESCAPE));
    ObjManager::Entry(new Map(Map::MapName::ESCAPEMAIN));

    //---ドアを生成---//
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));

    //---照明を生成---//
    ObjManager::Entry(new NomalLight(VGet(23, 32, 10)));
    ObjManager::Entry(new NomalLight(VGet(170, 32, -15)));

    //---プレイヤー生成---//
    ObjManager::Entry(new Player);


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