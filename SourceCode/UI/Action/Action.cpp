#include "Action.h"

		// @brief Action�R���X�g���N�^ //

Action::Action(VECTOR objpos)
	:ObjectBase(ObjectTag::UI)
	, objDistance(0)
	, canAction(false)
	, isAction(false)
	, actionBlend(nullptr)
{
	actionBlend = new BlendMode;
	objPos = objpos + VGet(0, 20, 0);
	objHandle = LoadGraph("../Assets/BackGround/Action.png");
}

		// @brief Action�f�X�g���N�^ //

Action::~Action()
{
	DeleteGraph(objHandle);
}

		// @brief Action�X�V���� //

void Action::Update(float deltaTime)
{
	ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
	objDistance = VSize(player->GetPos() - objPos);
	if (abs(objDistance) < actionRange)
	{
		actionBlend->AddFade();
		canAction = true;
		if (canAction && CheckHitKey(KEY_INPUT_E))
		{
			isVisible = false;
		}
	}
	else
	{
		actionBlend->SubFade();
		canAction = false;
	}
}

void Action::Draw()
{
	actionBlend->Fade();
	DrawExtendGraph3D(objPos.x, objPos.y, objPos.z, 0.3f, 0.3f, objHandle, TRUE);
	actionBlend->NoBlend();
}