#include "SceneManager.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include "../TitleScene/TitleScene.h"
#include"../PauseScene/PauseMenu/PauseMenu.h"
#include "../SaveScene/SaveScene.h"

SceneManager::SceneManager()
    :pause(new PauseScene)
    , gameSetting(new GameSetting)
    , timeMgr(new TimeManager)
    , pointLightShader(new PointLightShader)
{
    nowScreen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

SceneManager::~SceneManager()
{
    //処理なし
}

int SceneManager::Init()
{
    //ゲームのセッティング
    if (gameSetting->Init() == -1)
    {
        return -1;
    }

    //管理クラスの初期化
    ObjManager::Init();
    AssetManager::Init();

    //シーン関連のクラス初期化
    SaveScene::CreateInstance();
    PauseMenu::CreateInstance();

    //初期シーン設定
    nowScene.push(new TitleScene);
    SetDrawBright(255, 255, 255);
    return 0;
}

void SceneManager::Finalize()
{
    //シーン解放
    while(!nowScene.empty())
    {
        nowScene.pop();
    }
}

void SceneManager::UpdateScene()
{
    //シーンの更新処理
    storageScene = nowScene.top()->UpdateScene(timeMgr->DeltaTime());
}

void SceneManager::DrawScene()
{
    //現在のシーンを描画
    ClearDrawScreen();
    nowScene.top()->DrawScene();
    ScreenFlip();
}

void SceneManager::SwitchScene()
{
    if (nowScene.top() != storageScene)
    {
        //nowSceneがtmpSceneと異なっていたら解放して代入
        nowScene.pop();
        PauseMenu::ResetTitleButton();
        nowScene.push(storageScene);
    }
}

void SceneManager::CheckPauseMenu()
{
    //ポーズメニュー
    GetHitKeyStateAllEx(keyState);
    if (keyState[KEY_INPUT_ESCAPE] == 1)
    {
        SetMousePoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT);
        //配列のサイズでメニューの表示を切り替える
        if (nowScene.size() < MAX_STACK_SCENE)
        {
            //ゲーム画面保存
            SetDrawScreen(nowScreen);
            SaveDrawScreenToPNG(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_SCENE, -1);//PNG保存
            SetDrawScreen(DX_SCREEN_BACK);

            //メニュー画面表示
            SetMouseDispFlag(true);
            nowScene.push(new PauseScene);
            DeleteGraph(nowScreen);
        }
        else
        {
            SetMouseDispFlag(false);
            nowScene.pop();
        }
    }

    //タイトル画面移動時メニュー画面を消す
    if (PauseMenu::BackToTitle() && nowScene.size() >= MAX_STACK_SCENE)
    {
        nowScene.pop();
    }
}

void SceneManager::GameLoop()
{
    //ウィンドウが閉じられるまでループする
    while (ProcessMessage() == 0)
    {
        //ポーズメニュー
        CheckPauseMenu();

        //更新処理
        UpdateScene();

        //描画処理
        DrawScene();

        //シーン切り替え
        SwitchScene();

        if (!nowScene.top())
        {
            break;
        }
    }

    //ループ終了後の後処理
    Finalize();
}