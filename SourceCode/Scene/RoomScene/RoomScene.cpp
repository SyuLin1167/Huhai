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
#include "../PlayScene/PlayScene.h"
#include"../SaveScene/SaveScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
RoomScene::RoomScene()
    :SceneBase()
{
    //サウンド生成
    sound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor);
    sound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);

    //カメラ生成
    ObjManager::AddObj(new FpsCamera);

    //マップ生成
    ObjManager::AddObj(new Map(Map::MapTag::ROOM));

    //家具生成
    ObjManager::AddObj(new Furniture(Furniture::FurName::Room));

    //ベッド生成
    ObjManager::AddObj(new Bed);

    //照明生成
    ObjManager::AddObj(new NomalLight("room"));

    //プレイヤー生成
    ObjManager::AddObj(new Player);

    //台詞生成
    ObjManager::AddObj(new Remarks(TextType::Opening));
}

/// <summary>
/// デストラクタ
/// </summary>
RoomScene::~RoomScene()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
/// <returns>次フレームのシーン</returns>
SceneBase* RoomScene::UpdateScene(const float deltaTime)
{
    //オブジェクト更新
    ObjManager::UpdateAllObj(deltaTime);

    //オブジェクト当たり判定
    ObjManager::OnCollision();

    //アクションボタンが押されたら
    ObjBase* action = ObjManager::GetFirstObj(ObjTag::UI);
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
                ObjManager::DeleteAllObj();

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
        ObjManager::DeleteAllObj();

        //シーンをタイトルにする

        return new TitleScene;
    }
    return this;
}

/// <summary>
/// 描画処理
/// </summary>
void RoomScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::DrawAllObj();

    //フェード処理
    blendMode->Fade();
    DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK_SCREEN_COLOR, true);
    blendMode->NoBlend();
}