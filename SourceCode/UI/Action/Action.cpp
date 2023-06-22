#include "Action.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

// コンストラクタ //

Action::Action(VECTOR pos)
    :ObjBase(ObjectTag::UI)
    , toDistance(0)
    , canAction(false)
    , isAction(false)
    , actionBlend(nullptr)
{
    //アイコン設定
    objHandle = LoadGraph("../Assets/BackGround/Action.png");
    objPos = pos + VGet(0, 20, 0);

    actionBlend = new BlendMode();
}

// デストラクタ //

Action::~Action()
{
    //画像ハンドル削除
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

// 更新処理 //

void Action::Update(float deltaTime)
{
    //プレイヤーとの距離を測る
    ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    toDistance = VSize(player->GetPos() - objPos);

    //一定距離近づいたら
    if (abs(toDistance) < actionRange)
    {
        //アイコン表示
        actionBlend->AddFade(deltaTime);
        canAction = true;

        //Eキーが押されたら反応中にする
        if (canAction && CheckHitKey(KEY_INPUT_E))
        {
            isVisible = false;
            isAction = true;
        }
    }
    else
    {
        //一定距離離れたら非表示にする
        actionBlend->SubFade(deltaTime);
        canAction = false;
        isAction = false;
    }
}

// 描画処理 //

void Action::Draw()
{
    //アイコン描画
    actionBlend->Fade();
    DrawExtendGraph3D(objPos.x, objPos.y, objPos.z, 0.3f, 0.3f, objHandle, TRUE);
    actionBlend->NoBlend();
}