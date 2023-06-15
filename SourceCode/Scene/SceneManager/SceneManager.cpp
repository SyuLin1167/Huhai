#include "SceneManager.h"
#include<stack>

#include"../../GameSetting/GameSetting.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"
#include "../TitleScene/Title.h"

// コンストラクタ //

SceneManager::SceneManager()
    ://nowScene(nullptr)
    timeMgr(nullptr)
    , canLoop(true)
{
}

// デストラクタ //

SceneManager::~SceneManager()
{
    //管理クラスの後処理
    GameSetting::Finalize();
    ObjManager::Finalize();
    AssetManager::Finalize();

    //インスタンスの後処理
    //delete nowScene;
    delete timeMgr;

    while(!nowScene.empty())
    {
        nowScene.pop();
    }
}

// 初期化処理 //

int SceneManager::Init()
{
    //管理クラスの初期化
    if (GameSetting::Init() == -1)
    {
        return -1;
    }
    ObjManager::Init();
    AssetManager::Init();

    //インスタンス生成
    nowScene.push(new Title);
    //nowScene = new Title;
    timeMgr = new TimeManager;

    return 0;
}

// 更新処理 //

void SceneManager::Update()
{
    //一時的なシーン
    SceneBase* tmpScene;

    //シーンの更新処理
    timeMgr->Update();

    //tmpSceneに現在のシーンを代入
    tmpScene = nowScene.top()->Update(timeMgr->DeltaTime());

    if (!tmpScene)
    {
        canLoop = false;
    }

    if (nowScene.top() != tmpScene)
    {
        //NowSceneがtmpSceneと異なっていたら解放して代入
        //delete nowScene;
        //nowScene = tmpScene;
        nowScene.pop();
        nowScene.push(tmpScene);
    }
}

// 描画処理 //

void SceneManager::Draw()
{
    //現在のシーンを描画
    nowScene.top()->Draw();
}

// ゲームループ //

void SceneManager::GameLoop()
{
    //下記条件が成立するまでループ可能にする
    //(ウィンドウが閉じられるか、ESCキーが押されるか，ループが不可能になるか)
    while (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 0 || !canLoop)
    {
        //更新処理後画面を初期化
        Update();
        ClearDrawScreen();

        //描画処理後裏画面の内容を表描画に反映
        Draw();
        ScreenFlip();
    }
}