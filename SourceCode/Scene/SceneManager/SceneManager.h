#pragma once
#include<stack>

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
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw();

    /// <summary>
    /// ゲームループ
    /// </summary>
    void GameLoop();

private:
    bool canLoop;                               //ループフラグ

    std::stack<class SceneBase*> nowScene;      //現在のシーン

    class TimeManager* timeMgr;                 //タイムマネージャー
};

