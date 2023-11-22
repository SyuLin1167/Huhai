#include "Select.h"

#include"../../Asset/AssetManager/AssetManager.h"
#include"../../BlendMode/BlendMode.h"

Select::Select(SelectType type)
    :UIBase(ObjTag::UI)
    , selectBlend(nullptr)
{
    //ボタン設定
    objHandle = AssetManager::GetGraph(drawHandle[type]);
    objPos = drawPos[type];

    selectBlend = new BlendMode;
}

Select::~Select()
{
    //画像ハンドル削除
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

void Select::Update(const float deltaTime)
{
    //ボタンは開幕時フェード処理
    selectBlend->AddFade(deltaTime);

    //ボタン入力処理
    if (!isInput)
    {
        CanClick(BUTTON_WIDTH, BUTTON_HEIGHT);
        MouseClick();
    }
    
}

void Select::Draw()
{
    //フェード処理
    if (selectBlend->NowFade())
    {
        selectBlend->Fade();
    }
    //暗転処理
    else if (hasMauseClick)
    {
        selectBlend->Darken();
    }

    //画像描画
    DrawExtendGraph((int)objPos.x, (int)objPos.y,
        (int)objPos.x + BUTTON_WIDTH, (int)objPos.y + BUTTON_HEIGHT, objHandle, TRUE);
    selectBlend->NoBlend();
}