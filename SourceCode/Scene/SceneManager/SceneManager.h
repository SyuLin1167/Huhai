#pragma once

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
    bool canLoop;
    std::stack<class SceneBase*> nowScene;
    //class SceneBase* nowScene;
    class TimeManager* timeMgr;
};

