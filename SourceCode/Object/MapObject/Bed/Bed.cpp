#include "Bed.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../CharaObject/Camera/FixedCamera/FixedCamera.h"
#include"../../../UI/Action/Action.h"

/// <summary>
/// コンストラクタ
/// </summary>
Bed::Bed()
    :ObjBase(ObjTag::Furniture)
{
    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Bed/Bed.mv1");
    objPos = VGet( 55,0,20 );
    sleepPos = objPos + VGet(5, 0, 0);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / ONE_HALF_PI * DX_PI_F, 0.0f));

    //当たり判定設定
    colModel = objHandle;

    //アクションボタン生成
    ObjManager::AddObj(new Action(objPos));
}

/// <summary>
/// デストラクタ
/// </summary>
Bed::~Bed()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void Bed::Update(float deltaTime)
{
    //アクションボタンが押されたら就寝する
    ObjBase* action = ObjManager::GetFirstObj(ObjTag::UI);
    if (!action->IsVisible())
    {


        //プレイヤーをベッドに移動
        colModel = -1;
        ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
        VECTOR movePlyVec = sleepPos - player->GetPos();
        if (abs(VSize(movePlyVec)) >= 0)
        {
            movePlyVec = VNorm(movePlyVec);
            player->SetPos(player->GetPos() + (movePlyVec * objSpeed * deltaTime));
        }

        //視点を就寝時にする
        VECTOR aimDir = player->GetDir();
        if (aimDir.x > -1)
        {
            aimDir.x -= objSpeed * deltaTime;
        }
        ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
        camera->SetPos(camera->GetPos() - SLEEP_AIM_POS);
        camera->SetDir(aimDir);
    }
    else
    {
        //当たり判定更新
        ColUpdate();
    }
}

/// <summary>
/// 描画処理
/// </summary>
void Bed::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}
