#include "EscapeScene.h"

#include "../../Object/ObjectManager/ObjManager.h"
#include "../../Asset/AssetManager/AssetManager.h"
#include "../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Table/Table.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/FlashLight/FlashLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/Ghost.h"
#include"../PauseScene/PauseMenu/PauseMenu.h"
#include "../EndingScene/EndingScene.h"
#include"../TitleScene/TitleScene.h"
#include"../RoomScene/RoomScene.h"

EscapeScene::EscapeScene()
    :SceneBase()
{
    sceneName = "escape";

    //カメラ生成
    ObjManager::AddObj(new FpsCamera);

    //マップ生成
    ObjManager::AddObj(new Map(Map::MapTag::ESCAPE));
    ObjManager::AddObj(new Map(Map::MapTag::ESCAPEMAIN));
    ObjManager::AddObj(new Map(Map::MapTag::GOAL));

    //ドア生成
    class Door* door = new Door(sceneName);
    ObjManager::AddObj(door);
    door->MoveAnim(Door::AnimType::OPEN);
    ObjManager::AddObj(new Door(sceneName, "1"));
    ObjManager::AddObj(new Door(sceneName, "2"));

    //机生成
    for (int i = 0; i < TableNum; i++)
    {
        ObjManager::AddObj(new Table(i));
    }

    //照明生成
    ObjManager::AddObj(new BlinkingLight("escape"));
    ObjManager::AddObj(new NomalLight("escape", "1"));
    ObjManager::AddObj(new FlashLight);

    //プレイヤー生成
    ObjManager::AddObj(new Player);

    //ゴースト生成
    ObjManager::AddObj(new Ghost);

    //サウンド生成
    sound->AddSound("../Assets/Sound/GameOverSE.mp3", SoundTag::GameOver);
}

EscapeScene::~EscapeScene()
{
    //処理なし
}

SceneBase* EscapeScene::UpdateScene(const float deltaTime)
{
    //オブジェクト更新
    ObjManager::UpdateAllObj(deltaTime);

    //オブジェクト当たり判定
    ObjManager::OnCollision();

    //クリアしたら
    if (!ObjManager::GetObj(ObjTag::Map, 2))
    {
        //管理クラス内の確保したデータ解放
        ObjManager::DeleteAllObj();

        //シーンを次の場面にする
        return new EndingScene;
    }
    //ゲームオーバーしたら
    else if (!ObjManager::GetFirstObj(ObjTag::Player)->IsVisible())
    {
        //フェードアウト
        blendMode->AddFade(deltaTime);

        //シーン移行時の演出が終わったら
        sound->StartSoundOnce(SoundTag::GameOver, DX_PLAYTYPE_BACK);
        if (!sound->IsPlaying(SoundTag::GameOver))
        {
            if (!blendMode->NowFade())
            {
                //管理クラス内の確保したデータ解放
                AssetManager::ReleaseAllAsset();
                ObjManager::DeleteAllObj();

                //シーンを次の場面にする
                return new TitleScene;
            }
        }
    }

    //タイトルへ移動する場合
    if (PauseMenu::BackToTitle())
    {
        PauseMenu::ResetTitleButton();

        //管理クラス内の確保したデータ解放
        AssetManager::ReleaseAllAsset();
        ObjManager::DeleteAllObj();

        //シーンをタイトルにする
        return new TitleScene;
    }
    return this;
}

void EscapeScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::DrawAllObj();

    //フェード処理
    blendMode->Fade();
    DrawBox(bgX, bgY, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK_SCREEN_COLOR, true);
    blendMode->NoBlend();
}