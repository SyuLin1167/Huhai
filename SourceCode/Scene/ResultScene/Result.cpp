#include "Result.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../TitleScene/Title.h"
#include"../Save/Save.h"

// コンストラクタ //

ResultScene::ResultScene()
    :SceneBase()
{
    //台詞生成
    ObjManager::Entry(new Remarks(TextType::GameClear));

    //カメラ設定
    SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 20.0f, 0.0f), VGet(30.0f, 10.0f, 0.0f));
}

// デストラクタ //

ResultScene::~ResultScene()
{
}

// 更新処理 //

SceneBase* ResultScene::Update(float deltaTime)
{
    //オブジェクト更新
    ObjManager::Update(deltaTime);

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

void ResultScene::Draw()
{
    //オブジェクト描画
    ObjManager::Draw();
}