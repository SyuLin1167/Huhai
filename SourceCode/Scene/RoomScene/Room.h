#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

/*RoomSceneクラス*/
class Room :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Room();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Room();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>次フレームのシーン</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

private:
    class BlendMode* roomBlend;    //ブレンドモード
};
