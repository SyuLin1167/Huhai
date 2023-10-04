#include "Ending.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include"../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include"../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../TitleScene/TitleScene.h"
#include"../SaveScene/SaveScene.h"

// コンストラクタ //

Ending::Ending()
    :SceneBase()
{
    //カメラ生成
    ObjManager::Entry(new FixedCamera);

    //マップ生成
    ObjManager::Entry(new Map(Map::MapTag::ROOM));
    
    //家具生成
    ObjManager::Entry(new Furniture(Furniture::FurName::Room));

    //照明生成
    ObjManager::Entry(new NomalLight(VGet(40, 33, 0)));

    //台詞生成
    ObjManager::Entry(new Remarks(TextType::GameClear));
}

// デストラクタ //

Ending::~Ending()
{
}

// 更新処理 //

SceneBase* Ending::UpdateScene(const float deltaTime)
{
    //オブジェクト更新
    ObjManager::Update(deltaTime);

    //カメラ設定
    ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    camera->SetPos(VGet(50, 10, 10));
    camera->SetDir(VGet(10, 10, -10));

    //シーン移行時の演出が終わったら
    if (!ObjManager::GetFirstObj(ObjectTag::Remarks))
    {
        //管理クラス内の確保したデータ解放
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();

        //シーンを次の場面にする
        SaveScene::Save(nullptr);
        return new TitleScene;
    }
    return this;
}

// 描画処理 //

void Ending::DrawScene()
{
    //オブジェクト描画
    ObjManager::Draw();
}