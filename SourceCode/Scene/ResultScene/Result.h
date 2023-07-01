#pragma once
#include"../SceneBase/SceneBase.h"

/*ResultSceneクラス*/
class ResultScene :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ResultScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ResultScene();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <returns>次のフレームのシーン</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;
};
