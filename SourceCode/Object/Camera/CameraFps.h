#pragma once
#include<DxLib.h>
#include"../ObjectBase/ObjectBase.h"
#include"../ObjectManager/ObjManager.h"

const float CameraNear = 1.0f;       //カメラの描画範囲(近)
const float CameraFar = 2000.0f;     //カメラの描画範囲(遠)

/*一人称視点のクラス*/
class CameraFps:public ObjectBase
{
public:
    /// <summary>
    /// CamreFpsコンストラクター
    /// </summary>
    /// <param name="targetPos">カメラ注視座標</param>
    CameraFps();

    /// <summary>
    /// CamreFpsデストラクター
    /// </summary>
    ~CameraFps() {};

    /// <summary>
    /// CameraFps更新処理
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime)override;
private:
    int mouseX;
    int mouseY;
    VECTOR mousePos;
    VECTOR camLookPos;
};

