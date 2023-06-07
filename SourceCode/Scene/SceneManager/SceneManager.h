#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"


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
    /// NowScene更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// NowScene描画処理
    /// </summary>
    void Draw();

    /// <summary>
    /// ゲームループ
    /// </summary>
    void GameLoop();

private:
    bool isLoop;
    SceneBase* nowScene;
    TimeManager* timeMgr;
};

