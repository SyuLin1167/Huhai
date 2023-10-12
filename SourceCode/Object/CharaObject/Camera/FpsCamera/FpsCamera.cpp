#include "FpsCamera.h"

#include"../../../ObjectManager/ObjManager.h"
#include"../../Player/Player.h"
#include"../../../../Scene/PauseScene/PauseMenu/PauseMenu.h"

/// <summary>
/// コンストラクタ
/// </summary>
FpsCamera::FpsCamera()
    :ObjBase(ObjTag::Camera)
    , mouseX(0)
    , mouseY(0)
    , movePos{ 0,0,0 }
    , cameraYaw(0)
    , cameraPitch(-1)
{
    objDir = { 0,10,0 };
    SetCameraNearFar(CameraNear, CameraFar);                                    //カメラの描画範囲設定
    SetMouseDispFlag(false);                                                    //マウスは非表示
}

/// <summary>
/// デストラクタ
/// </summary>
FpsCamera::~FpsCamera()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void FpsCamera::Update(float deltaTime)
{
    //カメラはプレイヤーの目線にする
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        objPos = player->GetPos();
        objPos.y = CameraPosY;

        Move(deltaTime);

        //マウスポインターは画面の中心
        SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    else
    {
        isAlive = false;
    }
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void FpsCamera::Move(float deltaTime)
{
    //マウス移動量計測
    GetMousePoint(&mouseX, &mouseY);
    if (mouseX > MIN_MOVE_PARAM && mouseX < SCREEN_WIDTH - MIN_MOVE_PARAM &&
        mouseY > MIN_MOVE_PARAM && mouseY < SCREEN_HEIGHT - MIN_MOVE_PARAM)
    {
        movePos.x = (float)mouseX - static_cast<float>(SCREEN_WIDTH) / 2;
        movePos.y = (float)mouseY - static_cast<float>(SCREEN_HEIGHT) / 2;
    }


    //カーソルの移動量取得
    if (abs(movePos.x) > 0)
    {
        cameraYaw -= movePos.x * deltaTime * DX_PI_F / (255 - PauseMenu::Parameter("Sensitivity"));
    }
    if (abs(movePos.y) > 0)
    {
        cameraPitch -= movePos.y * deltaTime * DX_PI_F / (255 - PauseMenu::Parameter("Sensitivity"));
    }

    //カメラの方向設定
    objDir.x = cosf(cameraYaw);
    objDir.y = cameraPitch;
    objDir.z = sinf(cameraYaw);
}

/// <summary>
/// 描画処理
/// </summary>
void FpsCamera::Draw()
{
    //カーソルの移動した方向に視点を移動
    SetCameraPositionAndTarget_UpVecY(objPos, objPos + objDir);
}