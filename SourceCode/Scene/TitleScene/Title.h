#pragma once
#include"../SceneBase/SceneBase.h"
#include "../../UI/Select/Select.h"

/* TitleSceneクラス */
class Title :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Title();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Title();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>次のフレームのシーン</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

private:
    int screenGraph;        //画面保持グラフ

    class Door* door = nullptr;                 //ドア
    class BlendMode* titleBlend;                //ブレンドモード
    class Select* select[SelectTypeSize];       //選択ボタン
    class Sound* titleSound = nullptr;          //サウンド
};
