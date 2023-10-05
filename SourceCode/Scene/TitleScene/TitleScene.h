#pragma once

#include"../SceneBase/SceneBase.h"
#include "../../UI/Select/SelectType.h"

/* TitleSceneクラス */
class TitleScene :public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TitleScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TitleScene();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>次のフレームのシーン</returns>
    SceneBase* UpdateScene(const float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void DrawScene()override;

private:
    const int TITLE_POS_X = 180;                //タイトルロゴ座標X
    const int TITLE_POS_Y = 150;                //タイトルロゴ座標Y
    const int TITLE_SIZE_X = 450;               //タイトルロゴサイズX
    const int TITLE_SIZE_Y = 200;               //タイトルロゴサイズY

    int screenGraph;                            //画面保持グラフ

    class Door* door = nullptr;                 //ドア
    class Select* select[SelectTypeSize];       //選択ボタン
};
