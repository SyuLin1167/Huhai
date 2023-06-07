#include "SceneManager.h"
#include "../TitleScene/Title.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"

// コンストラクタ //

SceneManager::SceneManager()
    :nowScene(nullptr)
    , timeMgr(nullptr)
    , isLoop(true)
{
    //管理クラスの初期化
    AssetManager::Init();
    ObjManager::Init();
}

// デストラクタ //

SceneManager::~SceneManager()
{
    //インスタンスの後処理
    delete nowScene;

    //管理クラスの後処理
    ObjManager::Finalize();
    AssetManager::Finalize();
}

// 初期化処理 //

int SceneManager::Init()
{
    //画面モードのセット
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);
    SetWindowSizeExtendRate(1.0);

    //使用するDirect3Dのバージョン設定
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    //ウィンドウモードの変更
    ChangeWindowMode(TRUE);

    //アンチエイリアスを設定
    SetFullSceneAntiAliasingMode(4, 2);

    if (DxLib_Init() == -1)
    {
        //ライブラリ初期化でエラーが起きたら終了
        return -1;
    }

    //描画先を裏画面に変更
    SetDrawScreen(DX_SCREEN_BACK);

    //Zバッファ設定
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    //標準ライトを無効化
    SetLightEnable(FALSE);

    //インスタンス生成
    nowScene = new Title;
    timeMgr = new TimeManager;

    //初期化成功
    return 0;
}

// NowScene更新処理 //

void SceneManager::Update()
{
    //一時的なシーン
    SceneBase* tmpScene;

    //シーンの更新処理
    timeMgr->Update();

    //tmpSceneに現在のシーンを代入
    tmpScene = nowScene->Update(timeMgr->DeltaTime());

    if (!tmpScene)
    {
        isLoop = false;
    }

    if (nowScene != tmpScene)
    {
        //NowSceneがtmpSceneと異なっていたらNowSceneを解放
        delete nowScene;

        //現在のシーンにtmpSceneを代入
        nowScene = tmpScene;
    }
}

// NowScene描画処理 //

void SceneManager::Draw()
{
    //現在のシーンを描画
    nowScene->Draw();
}

// ゲームループ //

void SceneManager::GameLoop()
{
    //下記条件が成立するまでループ可能にする
    //(ウィンドウが閉じられるか、ESCキーが押されるか，ループが不可能になるか)
    while (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 0 || !isLoop)
    {
        //更新処理後画面を初期化
        Update();
        ClearDrawScreen();

        //描画処理後裏画面の内容を表描画に反映
        Draw();
        ScreenFlip();
    }

    //Dxライブラリの後処理
    DxLib_End();
}