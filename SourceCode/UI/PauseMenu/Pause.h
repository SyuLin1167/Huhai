#pragma once

#include"../../Scene/SceneBase/SceneBase.h"

class PauseMenu:public SceneBase
{
public:
    /// <summary>
    /// 初期化処理
    /// </summary>
    static PauseMenu* Init();

    /// <summary>
    /// 後処理
    /// </summary>
    static void Finalize();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>次フレームのシーン</returns>
    SceneBase* Update(float deltaTime) override;

    /// <summary>
    /// マウス入力処理
    /// </summary>
    void MouseInput();

    /// <summary>
    /// カメラの上下運動
    /// </summary>
    /// <returns>する:true|しない:false</returns>
    static bool IsMovementCamera() { if (pause) { return  pause->isSelect; }}

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;


private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PauseMenu();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~PauseMenu();

    static PauseMenu* pause;		//自身の実態

    int mouseX;
    int mouseY;
    bool canSelect;
    bool isSelect;                   //選択状態
    bool hasInput;                   //入力フラグ
};

