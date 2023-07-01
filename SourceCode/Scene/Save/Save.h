#pragma once

#include"../SceneBase/SceneBase.h"

/*SaveSceneクラス*/
class SaveScene
{
public:
    /// <summary>
    /// 初期化処理
    /// </summary>
    static void Init();

    /// <summary>
    /// セーブ処理
    /// </summary>
    /// <param name="scene">:シーン</param>
    static void Save(SceneBase* scene);
	
    /// <summary>
    /// ロード処理
    /// </summary>
    /// <returns>:セーブシーン</returns>
    static SceneBase* Load();

    /// <summary>
    /// 後処理
    /// </summary>
    static void Finalize();

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SaveScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SaveScene();

    static SaveScene* save;          //自身の実態
    SceneBase* saveScene;       //セーブシーン
};

