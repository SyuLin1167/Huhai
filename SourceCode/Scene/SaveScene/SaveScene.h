#pragma once

#include"../SceneBase/SceneBase.h"

/*SaveSceneクラス*/
class SaveScene
{
public:
    /// <summary>
    /// インスタンス生成処理
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// セーブ処理
    /// </summary>
    /// <param name="nowScene">:保存するシーン</param>
    static void Save(SceneBase* nowScene);
	
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
    /// コンストラクタ(シングルトン)
    /// </summary>
    SaveScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SaveScene();

    static std::unique_ptr<SaveScene> saveScene;        //自身の実態
    std::unique_ptr<SceneBase> scene;                   //セーブシーン
};

