#pragma once

#include"../SceneBase/SceneBase.h"

/*Endingクラス*/
class Ending :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Ending();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Ending();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <returns>次のフレームのシーン</returns>
    SceneBase* UpdateScene(const float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void DrawScene()override;
};
