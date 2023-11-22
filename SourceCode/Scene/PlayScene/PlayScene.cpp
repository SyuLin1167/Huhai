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
#include"../PauseScene/PauseMenu/PauseMenu.h"
#include"../TitleScene/TitleScene.h"
#include"../EscapeScene/EscapeScene.h"
#include"../SaveScene/SaveScene.h"

PlayScene::PlayScene()
    :SceneBase()
{
    sceneName = "play";

    //カメラ生成
    ObjManager::AddObj(new FpsCamera);

    //マップ生成
    ObjManager::AddObj(new Map(Map::MapTag::STAGE));

    //家具生成
    ObjManager::AddObj(new Furniture(Furniture::FurName::Stage));

    //ドア生成
    ObjManager::AddObj(new Door(sceneName));
    ObjManager::AddObj(new Door(sceneName, "1"));
    ObjManager::AddObj(new Door(sceneName, "2"));

    //イス生成
    ObjManager::AddObj(new Chair);

    //照明生成
    ObjManager::AddObj(new NomalLight(sceneName));
    ObjManager::AddObj(new LitLight(sceneName,"1"));
    ObjManager::AddObj(new LitLight(sceneName, "2"));
    ObjManager::AddObj(new NomalLight(sceneName, "3"));
    ObjManager::AddObj(new NomalLight(sceneName, "4"));

    //プレイヤー生成
    ObjManager::AddObj(new Player);

    //キャラギミック生成
    ObjManager::AddObj(new GhostWalkGim);
    ObjManager::AddObj(new Man);

    //台詞生成
    ObjManager::AddObj(new Remarks(TextType::Stage));
}

PlayScene::~PlayScene()
{
    //管理クラス内の確保したデータ解放
    AssetManager::ReleaseAllAsset();
    ObjManager::DeleteAllObj();
}

SceneBase* PlayScene::UpdateScene(const float deltaTime)
{
    //オブジェクト更新
    ObjManager::UpdateAllObj(deltaTime);

    //オブジェクト当たり判定
    ObjManager::OnCollision();

    //キャラクターのギミックが作動し終わったら
    ObjBase* man = ObjManager::GetFirstObj(ObjTag::Man);
    if (!man)
    {
        //管理クラス内の確保したデータ解放
        ObjManager::DeleteAllObj();

        //シーンを次の場面にする
        SaveScene::Save(this);
        return new EscapeScene;
    }

    //タイトルへ移動
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

void PlayScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::DrawAllObj();
}