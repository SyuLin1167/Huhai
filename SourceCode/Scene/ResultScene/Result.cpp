#include "Result.h"
#include "../TitleScene/Title.h"

// @brief ResultSceneコンストラクター //

Result::Result()
    :SceneBase()
{
    BgHandle = LoadGraph("../SourceCode/Assets/BackGround/Result.png");
}

// @brief ResultSceneデストラクター //

Result::~Result()
{
    if (BgHandle != -1)
    {
        DeleteGraph(BgHandle);
    }
}

// @brief ResultScene更新処理 //

SceneBase* Result::Update(float deltaTime)
{
    if (CheckHitKey(KEY_INPUT_T))
    {
        return new Title();
    }
    return this;
}

// @brief ResultScene描画処理 //

void Result::Draw()
{
    DrawGraph(BgX, BgY, BgHandle, TRUE);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Result画面:TでTitleシーンへ移行");
}