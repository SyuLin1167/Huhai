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

/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
    :SceneBase()
{
    //カメラ生成
    ObjManager::AddObj(new FpsCamera);

    //マップ生成
    ObjManager::AddObj(new Map(Map::MapTag::STAGE));

    //家具生成
    ObjManager::AddObj(new Furniture(Furniture::FurName::Stage));

    //ドア生成
    ObjManager::AddObj(new Door("play"));
    ObjManager::AddObj(new Door("play", "1"));
    ObjManager::AddObj(new Door("play", "2"));

    //イス生成
    ObjManager::AddObj(new Chair);

    //照明生成
    ObjManager::AddObj(new NomalLight("play"));
    ObjManager::AddObj(new LitLight("play","1"));
    ObjManager::AddObj(new LitLight("play", "2"));
    ObjManager::AddObj(new NomalLight("play", "3"));
    ObjManager::AddObj(new NomalLight("play", "4"));

    //プレイヤー生成
    ObjManager::AddObj(new Player);

    //キャラギミック生成
    ObjManager::AddObj(new GhostWalkGim);
    ObjManager::AddObj(new Man);

    //台詞生成
    ObjManager::AddObj(new Remarks(TextType::Stage));
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
    //管理クラス内の確保したデータ解放
    AssetManager::ReleaseAllAsset();
    ObjManager::DeleteAllObj();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
/// <returns>次のフレームのシーン</returns>
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

/// <summary>
/// 描画処理
/// </summary>
void PlayScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::DrawAllObj();
}