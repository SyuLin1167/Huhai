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
    /// 後処理
    /// </summary>
    void Finalize();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw();

    /// <summary>
    /// シーン切り替え
    /// </summary>
    void SceneChange();

    /// <summary>
    /// ゲームループ
    /// </summary>
    void GameLoop();

private:
    int keyState[256] = { 0 };                  //キーステータス

    std::stack<class SceneBase*> nowScene;      //現在のシーン
    SceneBase* tmpScene;                        //一時的なシーン

    class GameSetting* gameSetting;             //ゲームセッティング
    class TimeManager* timeMgr;                 //タイムマネージャー
};

