#include "Result.h"
#include "../TitleScene/Title.h"

// @brief ResultScene�R���X�g���N�^�[ //

Result::Result()
    :SceneBase()
{
    BgHandle = LoadGraph("../Assets/BackGround/Result.png");
}

// @brief ResultScene�f�X�g���N�^�[ //

Result::~Result()
{
    if (BgHandle != -1)
    {
        DeleteGraph(BgHandle);
    }
}

// @brief ResultScene�X�V���� //

SceneBase* Result::Update(float deltaTime)
{
    if (CheckHitKey(KEY_INPUT_T))
    {
        return new Title();
    }
    return this;
}

// @brief ResultScene�`�揈�� //

void Result::Draw()
{
    DrawGraph3D((float)BgX, 0,0, BgHandle, TRUE);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Result���:T��Title�V�[���ֈڍs");
}