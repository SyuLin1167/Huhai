#include "SceneManager.h"
#include "../TitleScene/Title.h"
#include "../PlayScene/Play.h"
#include"../../Shade/Bloom/Bloom.h"

// @brief SceneManagerコンストラクター //

SceneManager::SceneManager()
    :nowScene(new Title())
    , timeManager(new TimeManager)
{
    Bloom::Init();
}

// @brief SceneManagerデストラクター //

SceneManager::~SceneManager()
{
    delete nowScene;
}

// @brief　SceneManager更新処理 //

void SceneManager::Update()
{
    SceneBase* tmpScene;     //一時的なシーン
    timeManager->Update();
    Bloom::SetColoerScreen();
    //---シーンの更新処理---//
    tmpScene = nowScene->Update(timeManager->DeltaTime());     //tmpSceneに現在のシーンを代入
    if (nowScene != tmpScene)                                  //現在のシーンがtmpSceneと異なっていたら
    {
        delete nowScene;                                       //現在のシーンを解放
        nowScene = tmpScene;                                   //現在のシーンにtmpSceneを代入
    }
}

// @brief 現在のシーンの描画 //

void SceneManager::Draw()
{
    nowScene->Draw();
    Bloom::DrawUpdate();
}