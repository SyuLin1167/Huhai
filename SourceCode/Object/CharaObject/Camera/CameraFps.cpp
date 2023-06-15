#include "CameraFps.h"
#include"../Player/Player.h"

        // コンストラクター //

CameraFps::CameraFps()
    :ObjectBase(ObjectTag::Camera)
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
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);            //プレイヤーオブジェクト取得
    if (player)                                                                 //オブジェクトの中身が空でなければ
    {
        //---カメラ座標設定---//
        objPos = player->GetPos() + VGet(0.0f, 22.5f, 0.0f);                    //カメラの位置はプレイヤーの座標かつ目線の高さ

        Move(deltaTime);
        SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);                         //マウス座標を画面の中心にセット
    }
}

        // 移動処理 //

void CameraFps::Move(float deltaTime)
{
    //---マウス座標からスクリーン座標の中心を引く---//
    GetMousePoint(&mouseX, &mouseY);                                         //マウス座標取得
    movePos.x = (float)mouseX - static_cast<float>(SCREEN_WIDTH) / 2;
    movePos.y = (float)mouseY - static_cast<float>(SCREEN_HEIGHT) / 2;

    //---視点移動--//
    if (abs(movePos.x) > 0)                                                 //マウスカーソルX方向スライド時
    {
        cameraYaw -= movePos.x * deltaTime * DX_PI_F / 30;                      //カーソルの移動量分水平方向に回転
    }
    if (abs(movePos.y) > 0)                                                 //マウスカーソルY方向スライド時
    {
        cameraPitch -= movePos.y * deltaTime * DX_PI_F / 30;                  //カーソルの移動量分垂直方向に回転
    }

    //---注視点処理---//
    objDir.x = cosf(cameraYaw);
    objDir.y = cameraPitch;
    objDir.z = sinf(cameraYaw);
}

void CameraFps::Draw()
{
    SetCameraPositionAndTarget_UpVecY(objPos, objPos + objDir);         //プレイヤーの位置から注視点に向けてカメラをセット
}