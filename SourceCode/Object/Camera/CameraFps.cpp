#include "CameraFps.h"
#include"../Player/Player.h"

// @brief CameraFpsコンストラクター //

CameraFps::CameraFps()
    :ObjectBase(ObjectTag::Camera)
    ,camLookPos{0,15,0}
    ,mouseX(0)
    ,mouseY(0)
    ,movePos{0,0,0}
    ,cameraYaw(0)
    ,cameraPitch(0)
{
    SetCameraNearFar(CameraNear, CameraFar);                                            //カメラの描画範囲設定
}

// @brief CameraFps更新処理 //

void CameraFps::Update(float deltaTime)
{
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);                    //プレイヤーオブジェクト取得
    if (player)                                                                         //オブジェクトの中身が空でなければ
    {
        //---カメラ座標設定---//
        objPos = player->GetPos();                                                      //カメラの位置はプレイヤーの座標
        objPos.y = 15;                                                                  //高さは目線の位置

        Move(deltaTime);
        SetCameraPositionAndTarget_UpVecY(objPos, objPos + camLookPos);      //プレイヤーの位置から注視点に向けてカメラをセット
        objDir = camLookPos;                                                   //カメラの正面方向ベクトル
    }
    SetMousePoint(ScreenWidth / 2, ScreenHeight / 2);                        //マウス座標を画面の中心にセット
}

// @brief CameraFps移動処理 //

void CameraFps::Move(float deltaTime)
{
        GetMousePoint(&mouseX, &mouseY);                                        //マウス座標取得

        //---マウス座標からスクリーン座標の中心を引く---//
        movePos.x = mouseX - ScreenWidth / 2;
        movePos.y = mouseY - ScreenHeight / 2;

        //---視点移動--//
        if (abs(movePos.x) > 0)                                                      //マウスカーソルX方向スライド時
        {
            cameraYaw -= movePos.x *deltaTime* (float)DX_PI/30;                         //カーソルの移動量分水平方向に回転
        }
        if (abs(movePos.y) > 0)                                                     //マウスカーソルY方向スライド時
        {
            cameraPitch -= movePos.y * deltaTime * (float)DX_PI/30;                     //カーソルの移動領分垂直方向に回転
        }

        //---注視点処理---//
        camLookPos.x = cosf(cameraYaw);
        camLookPos.y = cameraPitch;
        camLookPos.z = sinf(cameraYaw);
}
