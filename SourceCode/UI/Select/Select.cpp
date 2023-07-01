#include "Select.h"

#include"../../BlendMode/Wipe.h"

// コンストラクタ //

Select::Select(SelectType type)
    :ObjBase(ObjectTag::UI)
    , mouseX(0)
    , mouseY(0)
    , canSelect(false)
    , isSelect(false)
    , hasInput(false)
    , selectBlend(nullptr)
{
    //ボタン設定
    objHandle = LoadGraph(drawHandle[type]);
    objPos = drawPos[type];

    selectBlend = new Wipe;
}

// デストラクタ //

Select::~Select()
{
    //画像ハンドル削除
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

// 更新処理 //

void Select::Update(float deltaTime)
{
    //ボタンは開幕時フェード処理
    selectBlend->AddFade(deltaTime);

    Collision();
    Input();
}

// 当たり判定処理 //

void Select::Collision()
{
    //マウスカーソル座標取得
    GetMousePoint(&mouseX, &mouseY);

    //マウスカーソルとボタンの当たり判定
    if (mouseX >= objPos.x && mouseX <= objPos.x + 160 &&
        mouseY >= objPos.y && mouseY <= objPos.y + 50)
    {
        //カーソルがボタン上にあったら選択可能
        canSelect = true;
    }
    else
    {
        //でなかったら選択不可
        canSelect = false;
    }
}

// 入力処理 //

void Select::Input()
{
    //入力可能だったら
    if (canSelect)
    {
        //ボタン上でクリックされたら
        if ((GetMouseInput() & MOUSE_INPUT_LEFT))
        {
            //ボタン入力中にする
            hasInput = true;
        }
        else if (hasInput)
        {
            //クリックし終わったら選択されたことにする
            isSelect = true;
            hasInput = false;
        }
    }
    else
    {
        //不可ならクリック中ボタン上から外れた場合を考慮して選択を取り消す
        hasInput = false;
    }
}

// 描画処理 //

void Select::Draw()
{
    //フェード処理
    if (selectBlend->NowFade())
    {
        selectBlend->Fade();
    }
    //暗転処理
    else if (hasInput)
    {
        selectBlend->Darken();
    }

    //画像描画
    DrawExtendGraph((int)objPos.x, (int)objPos.y, (int)objPos.x + 160, (int)objPos.y + 50, objHandle, TRUE);
    selectBlend->NoBlend();
}