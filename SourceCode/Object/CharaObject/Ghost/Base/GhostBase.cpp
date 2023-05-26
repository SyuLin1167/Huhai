#include "GhostBase.h"

GhostBase::GhostBase()
    :ObjectBase(ObjectTag::Ghost)
    , gstAnim(nullptr)
    , animType(IDLE)
{
    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../Assets/Chara/Ghost/GhostModel.mv1");        //モデル読み込み
    MV1SetScale(objHandle, VGet(0.02f, 0.02f, 0.02f));                                  //モデルのサイズ設定

    gstAnim = new Animation(objHandle);                                                 //アニメーションのインスタンス


    //---アニメーション読み込み---//
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostIdle.mv1");               //待機:0
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostWalk.mv1");                //走る:1
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostSad.mv1");                //走る:1
    gstAnim->AddAnimation("../Assets/Chara/Ghost/GhostMove.mv1");                //走る:1

    //---アニメーション状態セット---//
    gstAnim->StartAnim(animType);
    objDir = VGet(-1.0f, 0.0f, 0.0f);                                                   //初期方向
    MV1SetPosition(objHandle, objPos);                                                  //ポジション設定
}

GhostBase::~GhostBase()
{
    AssetManager::ReleaseMesh(objHandle);
    if (objHandle != -1)
    {
        MV1DeleteModel(objHandle);
    }
    delete gstAnim;
}