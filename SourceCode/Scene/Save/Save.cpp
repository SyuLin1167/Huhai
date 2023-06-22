#include "Save.h"

//実態へのポインタ定義
SaveScene* SaveScene::save = nullptr;

// コンストラクタ //

SaveScene::SaveScene()
    :saveScene(nullptr)
{
}

// デストラクタ //

SaveScene::~SaveScene()
{
}

// 初期化処理 //

void SaveScene::Init()
{
    //インスタンス生成
    if (!save)
    {
        save = new SaveScene;
    }
}

// 後処理 //

void SaveScene::Finalize()
{
    //インスタンス削除 
    if (save->saveScene)
    {
        delete save->saveScene;
    }
    if (save)
    {
        delete save;
    }
}

// セーブ処理 //

void SaveScene::Save(SceneBase* scene)
{
    //シーンをセーブ
    if (save->saveScene != scene)
    {
        save->saveScene = scene;
    }
}