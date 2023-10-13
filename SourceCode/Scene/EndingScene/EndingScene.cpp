#include "EndingScene.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include"../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include"../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../TitleScene/TitleScene.h"
#include"../SaveScene/SaveScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
EndingScene::EndingScene()
    :SceneBase()
{
    //カメラ生成
    ObjManager::AddObj(new FixedCamera);

    //マップ生成
    ObjManager::AddObj(new Map(Map::MapTag::ROOM));
    
    //家具生成
    ObjManager::AddObj(new Furniture(Furniture::FurName::Room));
    //照明生成
    ObjManager::AddObj(new NomalLight("EndingScene"));

    //台詞生成
    ObjManager::AddObj(new Remarks(TextType::GameClear));
}

/// <summary>
/// デストラクタ
/// </summary>
EndingScene::~EndingScene()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
/// <returns>次フレームのシーン</returns>
SceneBase* EndingScene::UpdateScene(const float deltaTime)
{
    //オブジェクト更新
    ObjManager::UpdateAllObj(deltaTime);

    //カメラ設定
    ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
    camera->SetPos(VGet(50, 10, 10));
    camera->SetDir(VGet(10, 10, -10));

    //シーン移行時の演出が終わったら
    if (!ObjManager::GetFirstObj(ObjTag::Remarks))
    {
        //管理クラス内の確保したデータ解放
        AssetManager::ReleaseAllAsset();
        ObjManager::DeleteAllObj();

        //シーンを次の場面にする
        SaveScene::Save(nullptr);
        return new TitleScene;
    }
    return this;
}

/// <summary>
/// 描画処理
/// </summary>
void EndingScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::DrawAllObj();
}