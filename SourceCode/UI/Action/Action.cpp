#include "Action.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">:描画座標</param>
Action::Action(VECTOR pos)
    :UIBase(ObjTag::UI)
    , toDistance(0)
    , canAction(false)
    , isAction(false)
    , actionBlend(nullptr)
{
    //アイコン設定
    objHandle = LoadGraph("../Assets/BackGround/Action.png");
    objPos = pos + ACTION_ICON_POS_Y;

    actionBlend = new BlendMode;
}

/// <summary>
/// デストラクタ
/// </summary>
Action::~Action()
{
    //画像ハンドル削除
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void Action::Update(float deltaTime)
{
    //プレイヤーとの距離を測る
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        toDistance = VSize(player->GetPos() - objPos);

        //一定距離近づいたら
        if (abs(toDistance) < actionRange)
        {
            //アイコン表示
            actionBlend->AddFade(deltaTime);
            canAction = true;

            //Eキーが押されたら反応中にする
            if (canAction && KeyStatus(KEY_INPUT_E) == 1)
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
}

/// <summary>
/// 描画処理
/// </summary>
void Action::Draw()
{
    //アイコン描画
    actionBlend->Fade();
    DrawExtendGraph3D(objPos.x, objPos.y, objPos.z, EXTEND_RATE, EXTEND_RATE, objHandle, TRUE);
    actionBlend->NoBlend();
}