#include "Select.h"

// @brief Select�R���X�g���N�^ //

Select::Select(SelectType type)
    :ObjectBase(ObjectTag::UI)
    , selectBlend(nullptr)
    , mouseX(0)
    , mouseY(0)
    , isSelect(false)
    , nowInput(false)
{
    selectBlend = new BlendMode;
    objPos = drawPos[type];
    objHandle = LoadGraph(drawHandle[type]);
}

// @brief Select�f�X�g���N�^ //

Select::~Select()
{
    DeleteGraph(objHandle);                         //�n���h���̊J��
}

// @brief Select�X�V���� //

void Select::Update(float deltaTime)
{
    selectBlend->AddFade();
    GetMousePoint(&mouseX, &mouseY);                //�}�E�X���W�擾

    if (mouseX >= objPos.x && mouseX <= objPos.x + 160 &&
        mouseY >= objPos.y && mouseY <= objPos.y + 50)
    {
        OnCollisionEnter();
    }
    else
    {
        nowInput = false;
    }
}

void Select::OnCollisionEnter()
{

		if ((GetMouseInput() & MOUSE_INPUT_LEFT))
		{
			nowInput = true;
		}
		else if (nowInput)
		{
			isSelect = true;
			nowInput = false;
		}
}

void Select::Draw()
{
	if (!isSelect)
	{
		selectBlend->Fade();
	}
	if(nowInput)
	{
		selectBlend->Darken();
	}
	DrawExtendGraph((int)objPos.x, (int)objPos.y, (int)objPos.x + 160, (int)objPos.y + 50, objHandle, TRUE);
	selectBlend->NoBlend();
}