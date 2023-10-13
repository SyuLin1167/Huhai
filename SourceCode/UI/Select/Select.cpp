#include "Select.h"

#include"../../Asset/AssetManager/AssetManager.h"
#include"../../BlendMode/BlendMode.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="type">:�{�^���^�C�v</param>
Select::Select(SelectType type)
    :UIBase(ObjTag::UI)
    , selectBlend(nullptr)
{
    //�{�^���ݒ�
    objHandle = AssetManager::GetGraph(drawHandle[type]);
    objPos = drawPos[type];

    selectBlend = new BlendMode;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Select::~Select()
{
    //�摜�n���h���폜
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
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

/// <summary>
/// �`�揈��
/// </summary>
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