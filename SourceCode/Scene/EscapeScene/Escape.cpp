#include "Escape.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Asset/Sound/Sound.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include"../../Object/MapObject/Table/Table.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/FlashLight/FlashLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include"../../Object/CharaObject/Ghost/Ghost.h"
#include"../../BlendMode/BlendMode.h"
#include "../ResultScene/Result.h"
#include"../TitleScene/Title.h"
#include"../RoomScene/Room.h"

// コンストラクタ //

EscapeScene::EscapeScene()
    :SceneBase()
    , escBlend(nullptr)
    , escSound(nullptr)
{
    //カメラ生成
    ObjManager::Entry(new CameraFps);

    //マップ生成
    ObjManager::Entry(new Map(Map::MapTag::ESCAPE));
    ObjManager::Entry(new Map(Map::MapTag::ESCAPEMAIN));
    ObjManager::Entry(new Map(Map::MapTag::GOAL));

    //ドア生成
    ObjManager::Entry(new Door(VGet(55, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(187, 0, 0), VGet(0, 180, 0)));
    ObjManager::Entry(new Door(VGet(759, 0, 0), VGet(0, 180, 0)));

    //机生成
    for (int i = 0; i < TableNum; i++)
    {
        ObjManager::Entry(new Table(i));
    }

    //照明生成
    ObjManager::Entry(new BlinkingLight(VGet(23, 32, 10)));
    ObjManager::Entry(new NomalLight(VGet(175, 32, -30)));
    ObjManager::Entry(new FlashLight());

    //プレイヤー生成
    ObjManager::Entry(new Player);

    //ゴースト生成
    ObjManager::Entry(new Ghost);

    //ブレンドモード生成
    escBlend = new BlendMode;

    //サウンド生成
    escSound = new Sound;
    escSound->AddSound("../Assets/Sound/EscapeBgm.mp3", SoundTag::Escape, 150);
    escSound->AddSound("../Assets/Sound/GameOverSE.mp3", SoundTag::GameOver, 150);
    escSound->StartSound(SoundTag::Escape, DX_PLAYTYPE_LOOP);

}

// デストラクタ //

EscapeScene::~EscapeScene()
{

}

// 更新処理 //

SceneBase* EscapeScene::Update(float deltaTime)
{
    //オブジェクト更新
    ObjManager::Update(deltaTime);

    //オブジェクト当たり判定
    ObjManager::Collision();

    //クリアしたら
    if (!ObjManager::GetObj(ObjectTag::Map, 2))
    {
        //管理クラス内の確保したデータ解放
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();

        //シーンを次の場面にする
        return new Result;
    }
    //ゲームオーバーしたら
    else if (!ObjManager::GetFirstObj(ObjectTag::Player)->IsVisible())
    {
        //フェードアウト
        escBlend->AddFade(deltaTime);

        //シーン移行時の演出が終わったら
        escSound->StartSoundOnce(SoundTag::GameOver, DX_PLAYTYPE_BACK);
        if (!escSound->IsPlaying(SoundTag::GameOver))
        {
            if (!escBlend->NowFade())
            {
                //管理クラス内の確保したデータ解放
                AssetManager::ReleaseAllAsset();
                ObjManager::ReleaseAllObj();

                //シーンを次の場面にする
                return new Title;
            }
        }
    }
    return this;
}

// 描画処理 //

void EscapeScene::Draw()
{
    //オブジェクト描画
    ObjManager::Draw();

    //フェード処理
    escBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    escBlend->NoBlend();
}