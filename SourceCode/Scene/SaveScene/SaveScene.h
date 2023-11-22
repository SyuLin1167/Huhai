#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// シーンのセーブ
/// </summary>
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
    /// デストラクタ
    /// </summary>
    ~SaveScene();
private:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    SaveScene();

    static std::unique_ptr<SaveScene> singleton;        //自身の実態
    std::unique_ptr<SceneBase> scene;                   //セーブシーン
};

