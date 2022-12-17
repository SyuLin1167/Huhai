#pragma once
#include<DxLib.h>
#include "SceneBase/SceneBase.h"

/*タイトルシーンのクラス*/
class Title :public SceneBase
{
public:
    /// <summary>
    /// コンストラクター
    /// </summary>
    Title();

    /// <summary>
    /// デストラクター
    /// </summary>
    ~Title();

    /// <summary>
    /// TitleScene更新処理
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <returns>現在のシーンのポインタ</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// タイトルシーンの描画
    /// </summary>
    void Draw()override;

};

