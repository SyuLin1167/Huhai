#include "RoomScene.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../Object/MapObject/Bed/Bed.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../UI/Reamarks/Remarks.h"
#include"../PauseMenu/PauseMenu.h"
#include"../TitleScene/TitleScene.h"
#include "../PlayScene/Play.h"
#include"../SaveScene/SaveScene.h"

// コンストラクタ //

RoomScene::RoomScene()
    :SceneBase()
{
    //サウンド生成
    sound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor);
    sound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);

    //カメラ生成
    ObjManager::Entry(new FpsCamera);

    //マップ生成
    ObjManager::Entry(new Map(Map::MapTag::ROOM));

    //家具生成
    ObjManager::Entry(new Furniture(Furniture::FurName::Room));

    //ベッド生成
    ObjManager::Entry(new Bed);

    //照明生成
    ObjManager::Entry(new NomalLight(VGet(40, 33, 0)));

    //プレイヤー生成
    ObjManager::Entry(new Player);

    //台詞生成
    ObjManager::Entry(new Remarks(TextType::Opening));
}

// デストラクタ //

RoomScene::~RoomScene()
{
    //処理なし
}

// 更新処理 //

SceneBase* RoomScene::UpdateScene(const float deltaTime)
{
    //オブジェクト更新
    ObjManager::Update(deltaTime);

    //オブジェクト当たり判定
    ObjManager::Collision();
    //アクションボタンが押されたら
    ObjBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (action)
    {
        if (!action->IsVisible())
        {
            //フェードアウト
            blendMode->AddFade(deltaTime);

            //シーン移行時の演出が終わったら
            if (!blendMode->NowFade())
            {

                //管理クラス内の確保したデータ解放
                ObjManager::ReleaseAllObj();

                //シーンを次の場面にする
                return new PlayScene;
            }
        }
    }

    //タイトルへ移動
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

void RoomScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::Draw();

    //フェード処理
    blendMode->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    blendMode->NoBlend();
}