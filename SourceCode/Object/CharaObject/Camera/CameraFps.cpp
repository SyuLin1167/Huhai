#include "CameraFps.h"

#include"../../ObjectManager/ObjManager.h"
#include"../Player/Player.h"

// コンストラクター //

CameraFps::CameraFps()
    :ObjBase(ObjectTag::Camera)
    , mouseX(0)
    , mouseY(0)
    , movePos{ 0,0,0 }
    , cameraYaw(0)
    , cameraPitch(-1)
{
    objDir = { 0,10,0 };
    SetCameraNearFar(CameraNear, CameraFar);                                    //カメラの描画範囲設定
    SetMouseDispFlag(FALSE);                                                    //マウスは非表示

}

// 更新処理 //

void CameraFps::Update(float deltaTime)
{
    //カメラはプレイヤーの目線にする
    ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        objPos = player->GetPos() + VGet(0.0f, 22.5f, 0.0f);

        Move(deltaTime);
        SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
}

// 移動処理 //

void CameraFps::Move(float deltaTime)
{
    //常時マウスポインターは画面の中心
    GetMousePoint(&mouseX, &mouseY);
    movePos.x = (float)mouseX - static_cast<float>(SCREEN_WIDTH) / 2;
    movePos.y = (float)mouseY - static_cast<float>(SCREEN_HEIGHT) / 2;

    //カーソルの移動量取得
    if (abs(movePos.x) > 0)
    {
        cameraYaw -= movePos.x * deltaTime * DX_PI_F / 30;
    }
    if (abs(movePos.y) > 0)
    {
        cameraPitch -= movePos.y * deltaTime * DX_PI_F / 30;
    }

    //カメラの方向設定
    objDir.x = cosf(cameraYaw);
    objDir.y = cameraPitch;
    objDir.z = sinf(cameraYaw);
}

void CameraFps::Draw()
{
    //カーソルの移動した方向に視点を移動
    SetCameraPositionAndTarget_UpVecY(objPos, objPos + objDir);
}