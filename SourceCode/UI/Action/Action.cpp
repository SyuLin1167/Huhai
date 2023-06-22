#include "Action.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

// �R���X�g���N�^ //

Action::Action(VECTOR pos)
    :ObjBase(ObjectTag::UI)
    , toDistance(0)
    , canAction(false)
    , isAction(false)
    , actionBlend(nullptr)
{
    //�A�C�R���ݒ�
    objHandle = LoadGraph("../Assets/BackGround/Action.png");
    objPos = pos + VGet(0, 20, 0);

    actionBlend = new BlendMode();
}

// �f�X�g���N�^ //

Action::~Action()
{
    //�摜�n���h���폜
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

// �X�V���� //

void Action::Update(float deltaTime)
{
    //�v���C���[�Ƃ̋����𑪂�
    ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    toDistance = VSize(player->GetPos() - objPos);

    //��苗���߂Â�����
    if (abs(toDistance) < actionRange)
    {
        //�A�C�R���\��
        actionBlend->AddFade(deltaTime);
        canAction = true;

        //E�L�[�������ꂽ�甽�����ɂ���
        if (canAction && CheckHitKey(KEY_INPUT_E))
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

// �`�揈�� //

void Action::Draw()
{
    //�A�C�R���`��
    actionBlend->Fade();
    DrawExtendGraph3D(objPos.x, objPos.y, objPos.z, 0.3f, 0.3f, objHandle, TRUE);
    actionBlend->NoBlend();
}