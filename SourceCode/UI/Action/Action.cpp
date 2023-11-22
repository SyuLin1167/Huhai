#include "Action.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

Action::Action(VECTOR pos)
    :UIBase(ObjTag::UI)
    , toDistance(0)
    , canAction(false)
    , isAction(false)
    , actionBlend(nullptr)
{
    //�A�C�R���ݒ�
    objHandle = LoadGraph("../Assets/BackGround/Action.png");
    objPos = pos + ACTION_ICON_POS_Y;

    actionBlend = new BlendMode;
}

Action::~Action()
{
    //�摜�n���h���폜
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

void Action::Update(const float deltaTime)
{
    //�v���C���[�Ƃ̋����𑪂�
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        toDistance = VSize(player->GetPos() - objPos);

        //��苗���߂Â�����
        if (abs(toDistance) < actionRange)
        {
            //�A�C�R���\��
            actionBlend->AddFade(deltaTime);
            canAction = true;

            //E�L�[�������ꂽ�甽�����ɂ���
            if (canAction && KeyStatus(KEY_INPUT_E) == 1)
            {
                isVisible = false;
                isAction = true;
            }
        }
        else
        {
            //��苗�����ꂽ���\���ɂ���
            actionBlend->SubFade(deltaTime);
            canAction = false;
            isAction = false;
        }
    }
}

void Action::Draw()
{
    //�A�C�R���`��
    actionBlend->Fade();
    DrawExtendGraph3D(objPos.x, objPos.y, objPos.z, EXTEND_RATE, EXTEND_RATE, objHandle, TRUE);
    actionBlend->NoBlend();
}