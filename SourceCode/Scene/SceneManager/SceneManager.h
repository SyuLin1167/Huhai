#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Time/TimeManager.h"


/*シーンマネージャーのクラス*/
class SceneManager
{
private:
    SceneBase* nowScene;
    TimeManager* timeManager;

public:
    /// <summary>
    /// コンストラクター
    /// </summary>
    SceneManager();

    /// <summary>
    /// デストラクター
    /// </summary>
    ~SceneManager();

    /// <summary>
    /// SceneManager更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 現在のシーンの描画
    /// </summary>
    void Draw();

    bool IsLoop() { return isLoop; }
private:
    bool isLoop;
};

