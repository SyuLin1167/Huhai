#pragma once

#include<stack>
#include<memory>
#include"../../GameSetting/GameSetting.h"
#include"../../Time/TimeManager.h"
#include"../../Shade/PointLight/PointLightShader.h"

/*SceneManagerクラス*/
class SceneManager
{

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneManager();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SceneManager();

    /// <summary>
    /// 初期化処理
    /// </summary>
    int Init();

    /// <summary>
    /// 後処理
    /// </summary>
    void Finalize();

    /// <summary>
    /// 更新処理
    /// </summary>
    void UpdateScene();

    /// <summary>
    /// 描画処理
    /// </summary>
    void DrawScene();

    /// <summary>
    /// シーン切り替え
    /// </summary>
    void SwitchScene();

    /// <summary>
    /// ポーズメニュー判定処理
    /// </summary>
    void CheckPauseMenu();

    /// <summary>
    /// ゲームループ
    /// </summary>
    void GameLoop();

private:
    int keyState[256] = { 0 };                  //キーステータス
    int nowScreen;                              //現在の画面

    std::stack<class SceneBase*> nowScene;      //現在のシーン
    SceneBase* tmpScene;                        //一時的なシーン

    std::unique_ptr<GameSetting> gameSetting;             //ゲームセッティング
    std::unique_ptr<TimeManager> timeMgr;                 //タイムマネージャー
    std::unique_ptr<PointLightShader> pointLightShader;           //ポイントライトシェーダー
};

