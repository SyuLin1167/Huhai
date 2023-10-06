#include "Escape.h"

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
#include"../PauseMenu/PauseMenu.h"
#include "../Ending/Ending.h"
#include"../TitleScene/TitleScene.h"
#include"../RoomScene/RoomScene.h"

// コンストラクタ //

EscapeScene::EscapeScene()
    :SceneBase()
{
    //カメラ生成
    ObjManager::Entry(new FpsCamera);

    //マップ生成
    ObjManager::Entry(new Map(Map::MapTag::ESCAPE));
    ObjManager::Entry(new Map(Map::MapTag::ESCAPEMAIN));
    ObjManager::Entry(new Map(Map::MapTag::GOAL));

    //ドア生成
    class Door* door = new Door("escape");
    ObjManager::Entry(door);
    door->MoveAnim(Door::AnimType::OPEN);
    ObjManager::Entry(new Door("escape", "1"));
    ObjManager::Entry(new Door("escape", "2"));

    //机生成
    for (int i = 0; i < TableNum; i++)
    {
        ObjManager::Entry(new Table(i));
    }

    //照明生成
    ObjManager::Entry(new BlinkingLight("escape"));
    ObjManager::Entry(new NomalLight("escape", "1"));
    ObjManager::Entry(new FlashLight);

    //プレイヤー生成
    ObjManager::Entry(new Player);

    //ゴースト生成
    ObjManager::Entry(new Ghost);

    //サウンド生成
    sound->AddSound("../Assets/Sound/GameOverSE.mp3", SoundTag::GameOver);
}

// デストラクタ //

EscapeScene::~EscapeScene()
{
    //処理なし
}

// 更新処理 //

SceneBase* EscapeScene::UpdateScene(float deltaTime)
{
    //オブジェクト更新
    ObjManager::Update(deltaTime);

    //オブジェクト当たり判定
    ObjManager::Collision();

    //クリアしたら
    if (!ObjManager::GetObj(ObjectTag::Map, 2))
    {
        //管理クラス内の確保したデータ解放
        ObjManager::ReleaseAllObj();

        //シーンを次の場面にする
        return new Ending;
    }
    //ゲームオーバーしたら
    else if (!ObjManager::GetFirstObj(ObjectTag::Player)->IsVisible())
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
                ObjManager::ReleaseAllObj();

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
        ObjManager::ReleaseAllObj();

        //シーンをタイトルにする
        return new TitleScene;
    }
    return this;
}

// 描画処理 //

void EscapeScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::Draw();

    //フェード処理
    blendMode->Fade();
    DrawBox(bgX, bgY, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK_SCREEN_COLOR, true);
    blendMode->NoBlend();
}