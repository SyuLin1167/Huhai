#include "Man.h"
#include"../../../UI/Action/Action.h"
#include"../../../Scene/Reamarks/Remarks.h"

// @brief Manコンストラクタ //

Man::Man()
    :ObjectBase(ObjectTag::Man)
    , manAnim(nullptr)
    , rotateNow(false)
    , aimDir{ 0,0,0 }
    , addRemarks(false)
{
    Load();
}

// @brief Manデストラクタ //

Man::~Man()
{
    AssetManager::ReleaseMesh(objHandle);
    delete manAnim;
}

// @brief Man読み込み処理 //

void Man::Load()
{
    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../Assets/Chara/Man/ManModel.mv1");
    objPos = { -55.0f,0.0f,30.0f };
    objDir = { 0,0,-1 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.02f, 0.02f, 0.02f));


    manAnim = new Animation(objHandle);

    manAnim->AddAnimation("../Assets/Chara/Man/ManCrying.mv1");
    animType = CRYING;
    manAnim->StartAnim(animType);

    ObjManager::Entry(new Action(objPos + VGet(0, 0, 5)));

}

// @brief Man更新処理 //

void Man::Update(float deltaTime)
{
    manAnim->AddAnimTime(deltaTime);
    MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
    VECTOR negativeVec = VTransform(objDir, rotYMat);
    if (!ObjManager::GetFirstObj(ObjectTag::UI)->IsVisible())
    {
        rotateNow = true;
        aimDir = VSub(ObjManager::GetFirstObj(ObjectTag::Player)->GetPos(), objPos);
        aimDir = VNorm(aimDir);
        Rotate();
        if (!rotateNow && !addRemarks)
        {
            ObjManager::Entry(new Remarks(TextType::Day1Stage));
            addRemarks = true;
        }
    }

    // モデルに回転をセットする
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

// @brief Man描画処 //

void Man::Draw()
{
    MV1DrawModel(objHandle);
}

void Man::Rotate()
{
    if (rotateNow)
    {
        // 回転が目標角度に十分近ければ回転モード終了
        if (IsSameAngle(aimDir, objDir))
        {
            objDir = aimDir;
            rotateNow = false;
        }
        else
        {
            // 回転させる
            VECTOR interPolateDir;
            interPolateDir = RotForAimY(objDir, aimDir, 2.0f);

            // 回転が目標角度を超えていないか
            VECTOR cross1, cross2;
            cross1 = VCross(objDir, aimDir);
            cross2 = VCross(interPolateDir, aimDir);

            //目標角度を超えたら終了
            if (cross1.y * cross2.y < 0.0f)
            {
                interPolateDir = aimDir;
                rotateNow = false;
            }
            // 目標ベクトルに10度だけ近づけた角度
            objDir = interPolateDir;
        }
    }
}