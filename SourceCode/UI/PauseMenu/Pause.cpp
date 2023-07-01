#include "Pause.h"

//���Ԃւ̃|�C���^��`
PauseMenu* PauseMenu::pause = nullptr;

// �R���X�g���N�^ //

PauseMenu::PauseMenu()
    : mouseX(0)
    , mouseY(0)
    , canSelect(false)
    , isSelect(false)
    , hasInput(false)
{

}

// �f�X�g���N�^ //

PauseMenu::~PauseMenu()
{

}

// ���������� //

PauseMenu* PauseMenu::Init()
{
    //�C���X�^���X����
    if (!pause)
    {
        pause = new PauseMenu;
    }

    return pause;
}

// �㏈�� //

void PauseMenu::Finalize()
{
    //�C���X�^���X�폜
    if (pause)
    {
        delete pause;
    }
}

// �X�V���� //

SceneBase* PauseMenu::Update(float deltaTime)
{
    MouseInput();
    return pause;
}

// �}�E�X���͏��� //

void PauseMenu::MouseInput()
{
    //�}�E�X�J�[�\�����W�擾
    GetMousePoint(&mouseX, &mouseY);

    //�}�E�X�J�[�\���ƃ{�^���̓����蔻��
    if (mouseX >= BgX && mouseX <= BgX + 500 &&
        mouseY >= BgY && mouseY <= BgY + 500)
    {
        //�J�[�\�����{�^����ɂ�������I���\
        canSelect = true;
    }
    else
    {
        //�łȂ�������I��s��
        canSelect = false;
    }

    //���͉\��������
    if (canSelect)
    {
        //�{�^����ŃN���b�N���ꂽ��
        if ((GetMouseInput() & MOUSE_INPUT_LEFT))
        {
            //�{�^�����͒��ɂ���
            hasInput = true;
        }
        else if (hasInput)
        {
            //�N���b�N���I�������I�����ꂽ���Ƃɂ���
            pause->isSelect = !pause->isSelect;
            hasInput = false;
        }
    }
    else
    {
        //�s�Ȃ�N���b�N���{�^���ォ��O�ꂽ�ꍇ���l�����đI����������
        hasInput = false;
    }
}

// �`�揈�� //

void PauseMenu::Draw()
{
    DrawBox(0, 0, 500, 500, GetColor(255, 255, 255), isSelect);
}