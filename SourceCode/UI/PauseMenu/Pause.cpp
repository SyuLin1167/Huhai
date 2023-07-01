#include "Pause.h"

//実態へのポインタ定義
PauseMenu* PauseMenu::pause = nullptr;

// コンストラクタ //

PauseMenu::PauseMenu()
    : mouseX(0)
    , mouseY(0)
    , canSelect(false)
    , isSelect(false)
    , hasInput(false)
{

}

// デストラクタ //

PauseMenu::~PauseMenu()
{

}

// 初期化処理 //

PauseMenu* PauseMenu::Init()
{
    //インスタンス生成
    if (!pause)
    {
        pause = new PauseMenu;
    }

    return pause;
}

// 後処理 //

void PauseMenu::Finalize()
{
    //インスタンス削除
    if (pause)
    {
        delete pause;
    }
}

// 更新処理 //

SceneBase* PauseMenu::Update(float deltaTime)
{
    MouseInput();
    return pause;
}

// マウス入力処理 //

void PauseMenu::MouseInput()
{
    //マウスカーソル座標取得
    GetMousePoint(&mouseX, &mouseY);

    //マウスカーソルとボタンの当たり判定
    if (mouseX >= BgX && mouseX <= BgX + 500 &&
        mouseY >= BgY && mouseY <= BgY + 500)
    {
        //カーソルがボタン上にあったら選択可能
        canSelect = true;
    }
    else
    {
        //でなかったら選択不可
        canSelect = false;
    }

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
            pause->isSelect = !pause->isSelect;
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

void PauseMenu::Draw()
{
    DrawBox(0, 0, 500, 500, GetColor(255, 255, 255), isSelect);
}