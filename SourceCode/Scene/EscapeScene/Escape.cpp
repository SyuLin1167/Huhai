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
#include"../../Asset/Sound/Sound.h"
#include"../../BlendMode/BlendMode.h"
#include "../ResultScene/Result.h"
#include"../TitleScene/Title.h"

// @brief EscapeSceneコンストラクタ //

EscapeScene::EscapeScene()
	:SceneBase()
    ,escSound(nullptr)
{
    //---カメラ生成---//
    ObjManager::Entry(new CameraFps);

    //---マップを生成---//
    ObjManager::Entry(new Map(Map::MapName::ESCAPE));
    ObjManager::Entry(new Map(Map::MapName::ESCAPEMAIN));
    ObjManager::Entry(new Map(Map::MapName::GOAL));

    //---ドアを生成---//
    ObjManager::Entry(new Door(VGet(55, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(187, 0, 0), VGet(0, 180, 0)));
    ObjManager::Entry(new Door(VGet(759, 0, 0), VGet(0, 180, 0)));

    //---机を生成---//
    for (int i = 0; i < TableNum; i++)
    {
        ObjManager::Entry(new Table(i));
    }

    //---照明を生成---//
    ObjManager::Entry(new BlinkingLight(VGet(23, 32, 10)));
    ObjManager::Entry(new NomalLight(VGet(175, 32, -30)));
    ObjManager::Entry(new FlashLight());

    //---プレイヤー生成---//
    ObjManager::Entry(new Player);

    ObjManager::Entry(new Ghost);

    escBlend = new BlendMode(2);

    escSound = new Sound;
    escSound->AddSound("../Assets/Sound/EscapeBgm.mp3", SoundTag::Escape, 150);
    escSound->AddSound("../Assets/Sound/GameOverSE.mp3", SoundTag::GameOver, 150);
    escSound->StartSound(SoundTag::Escape, DX_PLAYTYPE_LOOP);
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

    if (!ObjManager::GetObj(ObjectTag::Map, 2))
    {
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();
        return new Result;
    }
    else if (!ObjManager::GetFirstObj(ObjectTag::Player)->IsVisible())
    {
        escBlend->AddFade();
        escSound->StartSoundOnce(SoundTag::GameOver, DX_PLAYTYPE_BACK);
        if (!escSound->IsPlaying(SoundTag::GameOver))
        {
            if (!escBlend->NowFade())
            {
                AssetManager::ReleaseAllAsset();
                ObjManager::ReleaseAllObj();
                return new Title;
            }
        }
    }
    return this;
}

// @brief EscapeScene描画処理 //

void EscapeScene::Draw()
{
    ObjManager::Draw();
    escBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    escBlend->NoBlend();
}