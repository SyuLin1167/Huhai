#include "SceneManager.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include "../TitleScene/TitleScene.h"
#include"../PauseScene/PauseMenu/PauseMenu.h"
#include "../SaveScene/SaveScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
    :pause(new PauseScene)
    , gameSetting(new GameSetting)
    , timeMgr(new TimeManager)
    , pointLightShader(new PointLightShader)
{
    nowScreen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
    //処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
/// <returns></returns>
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

/// <summary>
/// 後処理
/// </summary>
void SceneManager::Finalize()
{
    //シーン解放
    while(!nowScene.empty())
    {
        nowScene.pop();
    }
}

/// <summary>
/// 更新処理
/// </summary>
void SceneManager::UpdateScene()
{
    //シーンの更新処理
    storageScene = nowScene.top()->UpdateScene(timeMgr->DeltaTime());
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::DrawScene()
{
    //現在のシーンを描画
    ClearDrawScreen();
    nowScene.top()->DrawScene();
    ScreenFlip();
}

/// <summary>
/// シーン切り替え
/// </summary>
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

/// <summary>
/// ポーズメニュー処理
/// </summary>
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
            SaveDrawScreenToPNG(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "../Assets/BackGround/GameScene.png", -1);//PNG保存
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

/// <summary>
/// ゲームループ
/// </summary>
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