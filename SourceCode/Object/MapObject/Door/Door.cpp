#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Door.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Sound/Sound.h"
#include"../../../UI/Action/Action.h"

// コンストラクタ //

Door::Door(std::string scene, std::string num)
    :ObjBase(ObjectTag::Furniture)
    , doorAnim(nullptr)
    , animType(IDLE)
    , doorSound(nullptr)
    , rotateNow(true)
{

    //ファイル読み込み
    std::ifstream ifs("../SourceCode/Object/MapObject/Door/DoorData.json");
    rapidjson::Document doc;

    //ファイル解析
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();

    //データを読み取って座標・向きに代入
    auto& data = doc[scene.c_str()][num.c_str()];
    objPos.x = data["pos"].GetArray()[0].GetFloat();
    objPos.z = data["pos"].GetArray()[1].GetFloat();
    objDir.x = data["dir"].GetArray()[0].GetFloat();
    objDir.z = data["dir"].GetArray()[1].GetFloat();

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Door/Door.mv1");
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    //アニメーション設定
    doorAnim = new Animation(objHandle);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorOpen.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->StartAnim(animType);
    doorAnim->StopAnim();

    //当たり判定設定
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;

    //サウンド設定
    doorSound = new Sound;
    doorSound->AddSound("../Assets/Sound/DoorOpenSE.mp3", SoundTag::DoorOpen, true, true);
    doorSound->AddSound("../Assets/Sound/DoorCloseSE.mp3", SoundTag::DoorClose, true, true);

    //アクションボタン追加
    action = new Action(objPos);
    ObjManager::Entry(action);
}

// デストラクタ //

Door::~Door()
{
    //インスタンス削除
    delete doorAnim;
    delete doorSound;
}

// 更新処理 //

void Door::Update(float deltaTime)
{
    //アニメーション時間再生
    doorAnim->AddAnimTime(deltaTime);

    //ドアの開閉処理
    player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        //プレイヤーが近づいたらボタン表示
        VECTOR actionPos = player->GetPos() - objPos;
        actionPos = VNorm(actionPos);
        action->SetPos(objPos + actionPos + VGet(0, 20, 0));

        if (!doorAnim->IsPlaying())
        {

            //Eキー入力でドア開放
            if (!action->IsVisible())
            {
                if (animType != OPEN)
                {
                    MoveAnim(OPEN);
                }
            }
            //Qキー入力でドア閉鎖
            if (CheckHitKey(KEY_INPUT_Q))
            {
                if (animType == OPEN)
                {
                    MoveAnim(CLOSE);
                }
            }
        }
    }

    //モデルの回転
    MATRIX rotYMat = MGetRotY(90.0f * (float)(DX_PI / 180.0f));
    VECTOR negativeVec = VTransform(objDir, rotYMat);
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    //当たり判定更新
    colModel = objHandle;
    ColUpdate();

    //サウンド更新
    doorSound->Doppler(SoundTag::DoorOpen, objPos);
    doorSound->Doppler(SoundTag::DoorClose, objPos);
}

// アニメーション処理 //

void Door::MoveAnim(int animtype)
{
    //指定したアニメーションを再生する
    if (animType != animtype)
    {
        animType = animtype;
        doorAnim->StartAnim(animType);
        if (animtype == OPEN)
        {
            action->SetVisible(false);
            doorSound->StartSound(SoundTag::DoorOpen, DX_PLAYTYPE_BACK);
        }
        else if (animtype == CLOSE)
        {
            doorSound->StartSound(SoundTag::DoorClose, DX_PLAYTYPE_BACK);
        }
    }
}

// 描画処理 //

void Door::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}