#include "SceneManager.h"

#include"../../GameSetting/GameSetting.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"
#include "../TitleScene/Title.h"
#include"../PauseMenu/PauseMenu.h"
#include "../Save/Save.h"


// コンストラクタ //

SceneManager::SceneManager()
    :gameSetting(nullptr)
    , timeMgr(nullptr)
    , tmpScene(nullptr)
{
    //インスタンス生成
    gameSetting = new GameSetting;
    timeMgr = new TimeManager;

    nowScreen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);

}

// デストラクタ //

SceneManager::~SceneManager()
{
    //インスタンスの後処理
    if (gameSetting)
    {
        delete gameSetting;
    }
    if (timeMgr)
    {
        delete timeMgr;
    }
}

// 初期化処理 //

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
    SaveScene::Init();
    PauseMenu::Init();

    //初期シーン設定
    nowScene.push(new TitleScene);
    SetDrawBright(255, 255, 255);
    return 0;
}

// 後処理 //

void SceneManager::Finalize()
{
    //管理クラスの後処理
    ObjManager::Finalize();
    AssetManager::Finalize();

    while(!nowScene.empty())
    {
        nowScene.pop();
    }

    //セッティングの後処理
    gameSetting->Finalize();
}

// 更新処理 //

void SceneManager::Update()
{
    //シーンの更新処理
    timeMgr->Update();

    //tmpSceneに現在のシーンを代入
    tmpScene = nowScene.top()->Update(timeMgr->DeltaTime());
}

// 描画処理 //

void SceneManager::Draw()
{
    //現在のシーンを描画
    ClearDrawScreen();
    nowScene.top()->Draw();
    ScreenFlip();
}

// シーン切り替え //

void SceneManager::SceneChange()
{
    if (nowScene.top() != tmpScene)
    {
        //nowSceneがtmpSceneと異なっていたら解放して代入
        nowScene.pop();
        nowScene.push(tmpScene);
    }
}

// ポーズメニュー処理 //

void SceneManager::Pause()
{
    //ポーズメニュー
    GetHitKeyStateAllEx(keyState);
    if (keyState[KEY_INPUT_ESCAPE] == 1)
    {
        SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        //配列のサイズでメニューの表示を切り替える
        if (nowScene.size() < 2)
        {
            //ゲーム画面保存
            SetDrawScreen(nowScreen);
            SaveDrawScreenToPNG(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "../Assets/BackGround/GameScene.png", -1);//PNG保存
            SetDrawScreen(DX_SCREEN_BACK);

            //メニュー画面表示
            SetMouseDispFlag(true);
            nowScene.push(PauseMenu::Init());
            DeleteGraph(nowScreen);
        }
        else
        {
            SetMouseDispFlag(false);
            nowScene.pop();
        }
    }

    //タイトル画面移動時メニュー画面を消す
    if (PauseMenu::BackToTitle() && nowScene.size() > 1)
    {
        nowScene.pop();
    }
}

// ゲームループ //

void SceneManager::GameLoop()
{
    //ウィンドウが閉じられるまでループする
    while (ProcessMessage() == 0)
    {
        //ポーズメニュー
        Pause();

        //更新処理
        Update();

        //描画処理
        Draw();

        //シーン切り替え
        SceneChange();

        if (!nowScene.top())
        {
            break;
        }
    }

    //ループ終了後の後処理
    Finalize();
}