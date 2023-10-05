#include "PlayScene.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include "../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/LightingLight/LitLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/MoveGimmic/GhostWalkGim.h"
#include"../../Object/CharaObject/Man/Man.h"
#include "../../UI/Reamarks/Remarks.h"
#include"../PauseMenu/PauseMenu.h"
#include"../TitleScene/TitleScene.h"
#include"../EscapeScene/Escape.h"
#include"../SaveScene/SaveScene.h"

// コンストラクタ //

PlayScene::PlayScene()
    :SceneBase()
{
    //カメラ生成
    ObjManager::Entry(new FpsCamera);

    //マップ生成
    ObjManager::Entry(new Map(Map::MapTag::STAGE));

    //家具生成
    ObjManager::Entry(new Furniture(Furniture::FurName::Stage));

    //ドア生成
    ObjManager::Entry(new Door("play"));
    ObjManager::Entry(new Door("play", "1"));
    ObjManager::Entry(new Door("play", "2"));

    //イス生成
    ObjManager::Entry(new Chair);

    //照明生成
    ObjManager::Entry(new NomalLight("play"));
    ObjManager::Entry(new LitLight("play","1"));
    ObjManager::Entry(new LitLight("play", "2"));
    ObjManager::Entry(new NomalLight("play", "3"));
    ObjManager::Entry(new NomalLight("play", "4"));

    //プレイヤー生成
    ObjManager::Entry(new Player);

    //キャラギミック生成
    ObjManager::Entry(new GhostWalkGim);
    ObjManager::Entry(new Man);

    //台詞生成
    ObjManager::Entry(new Remarks(TextType::Stage));
}

// デストラクタ //

PlayScene::~PlayScene()
{
}

// 更新処理 //

SceneBase* PlayScene::UpdateScene(const float deltaTime)
{
    //オブジェクト更新
    ObjManager::Update(deltaTime);

    //オブジェクト当たり判定
    ObjManager::Collision();

    //キャラクターのギミックが作動し終わったら
    ObjBase* man = ObjManager::GetFirstObj(ObjectTag::Man);
    if (!man)
    {
        //管理クラス内の確保したデータ解放
        ObjManager::ReleaseAllObj();

        //シーンを次の場面にする
        SaveScene::Save(this);
        return new EscapeScene;
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

void PlayScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::Draw();
}