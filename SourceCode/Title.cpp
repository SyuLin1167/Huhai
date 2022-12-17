#include "Title.h"
#include "Play.h"

// @brief TitleSceneコンストラクター //

Title::Title()
    :SceneBase()
{
    BgHandle = LoadGraph("SourceCode/Assets/BackGround/Title.png");
}

// @brief TitleSceneデストラクター //

Title::~Title()
{
    if (BgHandle != -1)
    {
        DeleteGraph(BgHandle);
    }
}

// @brief TitleScene更新処理 //

SceneBase* Title::Update(float deltaTime)
{
    if (CheckHitKey(KEY_INPUT_P))
    {
        return new Play();
    }
    return this;
}

// @brief TitleScene描画処理 //

void Title::Draw()
{
    DrawGraph(BgX, BgY, BgHandle, TRUE);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Title画面:PでPlayシーンへ移行");
}