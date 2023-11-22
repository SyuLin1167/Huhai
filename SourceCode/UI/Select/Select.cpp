#include "Select.h"

#include"../../Asset/AssetManager/AssetManager.h"
#include"../../BlendMode/BlendMode.h"

Select::Select(SelectType type)
    :UIBase(ObjTag::UI)
    , selectBlend(nullptr)
{
    //�{�^���ݒ�
    objHandle = AssetManager::GetGraph(drawHandle[type]);
    objPos = drawPos[type];

    selectBlend = new BlendMode;
}

Select::~Select()
{
    //�摜�n���h���폜
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

void Select::Update(const float deltaTime)
{
    //�{�^���͊J�����t�F�[�h����
    selectBlend->AddFade(deltaTime);

    //�{�^�����͏���
    if (!isInput)
    {
        CanClick(BUTTON_WIDTH, BUTTON_HEIGHT);
        MouseClick();
    }
    
}

void Select::Draw()
{
    //�t�F�[�h����
    if (selectBlend->NowFade())
    {
        selectBlend->Fade();
    }
    //�Ó]����
    else if (hasMauseClick)
    {
        selectBlend->Darken();
    }

    //�摜�`��
    DrawExtendGraph((int)objPos.x, (int)objPos.y,
        (int)objPos.x + BUTTON_WIDTH, (int)objPos.y + BUTTON_HEIGHT, objHandle, TRUE);
    selectBlend->NoBlend();
}