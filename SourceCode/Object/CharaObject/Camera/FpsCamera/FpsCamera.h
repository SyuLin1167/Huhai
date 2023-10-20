#pragma once

#include"../../../../GameSetting/GameSetting.h"
#include"../../../ObjectBase/ObjBase.h"

constexpr float CameraNear = 0.1f;       //カメラの描画範囲(近)
constexpr float CameraFar = 400.0f;      //カメラの描画範囲(遠)

constexpr float CameraPosY = 22.5f;      //カメラの高さ

/// <summary>
/// FpsCameraクラス
/// </summary>
class FpsCamera :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FpsCamera();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FpsCamera();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;
private:
    /// <summary>
    /// 移動処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Move(const float deltaTime);

    const float CONTROL_SENSI = 255;          //感度制御用

    int mouseX;                             //マウス座標X
    int mouseY;                             //マウス座標Y
    VECTOR movePos;                         //移動座標
    const int MIN_MOVE_PARAM = 30;          //最小移動量

    float cameraYaw;                        //水平方向回転角
    float cameraPitch;                      //垂直方向回転角
};
