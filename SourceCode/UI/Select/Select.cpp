#include "Select.h"

#include"../../BlendMode/BlendMode.h"

// �R���X�g���N�^ //

Select::Select(SelectType type)
    :ObjBase(ObjectTag::UI)
    , mouseX(0)
    , mouseY(0)
    , canSelect(false)
    , isSelect(false)
    , hasInput(false)
    , selectBlend(nullptr)
{
    //�{�^���ݒ�
    objHandle = LoadGraph(drawHandle[type]);
    objPos = drawPos[type];

    selectBlend = new BlendMode;
}

// �f�X�g���N�^ //

Select::~Select()
{
    //�摜�n���h���폜
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

// �X�V���� //

void Select::Update(float deltaTime)
{
    //�{�^���͊J�����t�F�[�h����
    selectBlend->AddFade(deltaTime);

    OnCollisionEnter();

}

// �����蔻�菈�� //

void Select::OnCollisionEnter()
{
    //�}�E�X�J�[�\�����W�擾
    GetMousePoint(&mouseX, &mouseY);

    //�}�E�X�J�[�\���ƃ{�^���̓����蔻��
    if (mouseX >= objPos.x && mouseX <= objPos.x + 160 &&
        mouseY >= objPos.y && mouseY <= objPos.y + 50)
    {
        //�J�[�\�����{�^����ɂ�������I���\
        canSelect = true;
        Input();
    }
    else
    {
        //�łȂ�������I��s��
        canSelect = false;
        hasInput = false;
    }
}

// ���͏��� //

void Select::Input()
{
    //���͉\��������
    if (canSelect)
    {

    }
    else
    {
        //�s�Ȃ�N���b�N���{�^���ォ��O�ꂽ�ꍇ���l�����đI����������
        //isSelect = false;
        //hasInput = false;
    }
    //�{�^����ŃN���b�N���ꂽ��
        if ((GetMouseInput() & MOUSE_INPUT_LEFT))
        {
            //�{�^�����͒��ɂ���
            hasInput = true;
        }
        else if (hasInput)
        {
            //�N���b�N���I�������I�����ꂽ���Ƃɂ���
            isSelect = true;
            hasInput = false;
        }
}

// �`�揈�� //

void Select::Draw()
{
    //�t�F�[�h����
    if (selectBlend->NowFade())
    {
        selectBlend->Fade();
    }
    //�Ó]����
    else if (hasInput)
    {
        selectBlend->Darken();
    }

    //�摜�`��
    DrawExtendGraph((int)objPos.x, (int)objPos.y, (int)objPos.x + 160, (int)objPos.y + 50, objHandle, TRUE);
    selectBlend->NoBlend();
}