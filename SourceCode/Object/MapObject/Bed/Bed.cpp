#include "Bed.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../CharaObject/Camera/FixedCamera/FixedCamera.h"
#include"../../../UI/Action/Action.h"
#include"../../../Scene/TitleScene/Title.h"

// コンストラクタ //

Bed::Bed()
    :ObjBase(ObjectTag::Furniture)
{
    Load();
}

// デストラクタ //

Bed::~Bed()
{
}

        // 読み込み処理 //

void Bed::Load()
{

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Bed/Bed.mv1");
    objPos = { 55,0,20 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));

    //当たり判定設定
    colModel = objHandle;

    //アクションボタン生成
    ObjManager::Entry(new Action(objPos));
}

        // 更新処理 //

void Bed::Update(float deltaTime)
{
    //アクションボタンが押されたら就寝する
    ObjBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (!action->IsVisible())
    {


        //プレイヤーをベッドに移動
        colModel = -1;
        ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
        VECTOR movePlyVec = (objPos + VGet(5.0f, 0.0f, 0.0f)) - player->GetPos();
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
        ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
        camera->SetPos(camera->GetPos() - VGet(0, 8, 0));
        camera->SetDir(aimDir);
    }
    else
    {
        //当たり判定更新
        ColUpdate();
    }
}

// 描画処理 //

void Bed::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}
