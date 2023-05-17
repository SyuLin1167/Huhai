#include "Bed.h"
#include"../../../UI/Action/Action.h"

// @brief Bedコンストラクタ //

Bed::Bed()
    :ObjectBase(ObjectTag::Furniture)
{
    Load();
}

// @brief Bedデストラクタ //

Bed::~Bed()
{
    AssetManager::ReleaseMesh(objHandle);                                               //モデルメッシュの削除
}

// @brief Bed読み込み処理 //

void Bed::Load()
{
    objPos = { 55,0,20 };                                                               //初期座標設定

    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../Assets/Map/Bed/Bed.mv1");                     //モデル読み込み

    MV1SetPosition(objHandle, objPos);                                                  //モデルの座標設定
    MV1SetScale(objHandle, objScale);                                                   //モデルのサイズ設定
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));        //モデルの向き設定

    ObjManager::Entry(new Action(objPos));
}

// @brief Bed更新処理 //

void Bed::Update(float deltaTime)
{
    ObjectBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (!action->IsVisible())
    {
        colModel = -1;
        ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
        VECTOR movePly = VSub(objPos + VGet(5.0f, 0.0f, 0.0f), player->GetPos());
        movePly = VNorm(movePly);
        player->SetPos(VAdd(player->GetPos(), movePly));

        ObjectBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
        SetCameraPositionAndTarget_UpVecY(camera->GetPos() - VGet(0, 8, 0), VGet(0, 25, 20));
    }
    else
    {
        colModel = objHandle;                                                               //当たり判定のモデルはオブジェクトのモデル
        ColUpdate();                                                                        //当たり判定更新
    }
}

// @brief Bed描画処理 //

void Bed::Draw()
{
    MV1DrawModel(objHandle);                                                            //モデル描画
}