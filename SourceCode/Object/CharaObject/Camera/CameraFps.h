#pragma once
#include<DxLib.h>
#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"

constexpr float CameraNear = 0.1f;       //カメラの描画範囲(近)
constexpr float CameraFar = 400.0f;     //カメラの描画範囲(遠)

/*一人称視点のクラス*/
class CameraFps:public ObjectBase
{
public:
    /// <summary>
    /// CamreFpsコンストラクター
    /// </summary>
    CameraFps();

    /// <summary>
    /// CamreFpsデストラクター
    /// </summary>
    ~CameraFps() {};

    /// <summary>
    /// CameraFps更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// CameraFps移動処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Move(float deltaTime);

private:
    //---マウス関連---//
    int mouseX;             //マウス座標X
    int mouseY;             //マウス座標Y
    VECTOR movePos;         //移動座標

    //---カメラ方向関連---//
    float cameraYaw;        //水平方向回転角
    float cameraPitch;      //垂直方向回転角
};

