#include "Remarks.h"
#include<unordered_map>

// �R���X�g���N�^ //

Remarks::Remarks(TextType texttype)
    :ObjBase(ObjectTag::Remarks)
    , textType(texttype)
    , stringBuf{}
    , holdBuf{}
    , Sn(0)
    , Sp(0)
    , eofFlag(false)
    , waitKey(false)
    , textX(0)
    , textY(0)
    , graph(MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT))
{
    //�e�L�X�g�{�b�N�X�ݒ�
    objHandle = LoadGraph("../Assets/BackGround/Remarks.png");
    objPos = VGet(0.0f, 600.0f, 0.0f);

    SetFontSize(TEXTSIZE);
}

// �f�X�g���N�^ //

Remarks::~Remarks()
{
    //�摜�n���h���폜
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

// �X�V���� //

void Remarks::Update(float deltaTime)
{
    //�����̓ǂݍ��ݒ��Ȃ�
    if (!eofFlag)
    {
        //�ҋ@���Ȃ�
        if (waitKey)
        {
            //���N���b�N���������܂őҋ@
            if ((GetMouseInput() & MOUSE_INPUT_LEFT))
            {
                waitKey = false;
            }
        }
        else
        {
            //�ҋ@���łȂ���Α䎌���ꕶ�����ǂݍ���
            char Moji = GetText(Sn, Sp);
            switch (Moji)
            {
            case '/':
                //�ҋ@������������ҋ@���ɂ���
                waitKey = true;

                //�ǂݍ��ݕ�����1�����i�߂�
                Sp++;
                break;

            case '^':
                //�I�������������當���ǂݍ��݂��I������
                eofFlag = true;
                break;

            case '|':
                //�N���A��������������ɕ\������Ă��镶���������
                for (int i = 0; i < BUFHEIGHT; i++)
                {
                    for (int j = 0; j < BUFWIDTH; j++)
                    {
                        //���z�e�L�X�g�o�b�t�@������
                        stringBuf[i][j] = 0;
                    }
                }

                //�`��ʒu������
                textX = 0;
                textY = 0;

                //�ǂݍ��ݕ�����1�����i�߂�
                Sp++;
                break;

            default:
                //���̑��̕�����������
                //1�������L��
                holdBuf[0] = GetText(Sn, Sp);
                holdBuf[1] = GetText(Sn, Sp + 1);
                holdBuf[2] = '\0';

                //�e�L�X�g�o�b�t�@�ɋL��������������
                stringBuf[textY][textX * 2] = holdBuf[0];
                stringBuf[textY][textX * 2 + 1] = holdBuf[1];

                //�ǂݍ��ݕ�����2�������i�߂�
                Sp += 2;

                //�����\���ʒu��1�����i�߂�
                textX++;

                //�����\���ʒu����������͂ݏo������s
                if (textX > BUFWIDTH)
                {
                    NewLine();
                }

                //�����Ō�܂œǂݍ��ݏI���������s���Ď��̕���ǂݍ���
                if (GetText(Sn, Sp) == '\0')
                {
                    NewLine();
                    Sn++;
                    Sp = 0;
                }
                break;
            }
        }
    }
    if (eofFlag)
    {
        //�䎌���ǂݏI�������I�u�W�F�N�g�폜�̂��ߎ��S�ɂ���
        isAlive = false;
    }
}

// ������擾���� //

char Remarks::GetText(int sn, int sp)
{
    //�I�[�v�j���O
    char Opening[][256] =
    {
        "�ŋߎd�������܂������Ȃ�...�B ",
        "/|�����������x���Ă��ꂽ�Ȃ����̂Ŗ������A ",
        "���ꂩ�炸���ƁA�����̐�����Ӗ������o���Ȃ��ł���B ",
        "/�����ƍȂƐG�ꍇ���Ă���Ηǂ������ƁA/�S��v���B",
        "/|�����Ǝ��́A���̎��̎��������ƈ��������Ă���̂��낤...�B ",
        "/^",
    };

    //�X�e�[�W
    char Stage[][256] =
    {
        "�����͈��...�B ",
        "/�������܂Ŏ����ŐQ�Ă����͂�����? ",
        "/|���ɂ��Ă͊��o���������肵�Ă���...�B ",
        "/|�C�����������A�i�ނ����Ȃ��̂��낤��? ",
        "/^ ",
    };

    //�j���Z���t
    char ManSpeak[][256] =
    {
        "�j���u...!?�v ",
        "/|�j���u�Ȃ��N�͂����ɂ���!�v ",
        "/|�����悤�Ƃ����������o���Ȃ��A/�������炾�낤��? ",
        "/���͔ނ̘b�𕷂����Ƃ����ł��Ȃ��悤���B ",
        "/|�j���u�����́A/�ߋ��Ɏ����Ă�����̂��W�܂�ꏊ�B�v ",
        "/�j���u�ߋ��̂����őO�ɐi�߂Ȃ��l���悭�Ă΂��B ",
        "/�����A�C�c���Ă�ł���񂾂Ɖ��͎v���B�v ",
        "/|�j���u�N���A�C�c�ɌĂ΂�Ă����ɂ���͂����B�v ",
        "/�j���u������? /�����ŃA�C�c�ɕ߂܂�����Ŋ��A ",
        "/�����ɂ͊F��̎��𐋂��Ă���B�v ",
        "/|�j���u3���ԁA /�Ƃɂ������c���瓦���؂�񂾁B ",
        "/��������΁A�A�C�c�����������B�v ",
        "/|�j���u....!?/�܂����A�A�C�c������! /���͂��������܂ł��A ",
        "/����������đ����������瓦�����!�v  ",
        "/^ ",
    };

    //�N���A
    char GameClear[][256] =
    {
        "���݃v���C�ł���̂͂����܂łɂȂ�܂��B",
        "/|�V��ł����������肪�Ƃ��������܂���!!!",
        "/^",
    };

    //�^�C�v�ɍ��킹���Z���t�̕�����Ԃ�
    switch (textType)
    {
    case TextType::Opening:
        return Opening[sn][sp];
        break;
    case TextType::Stage:
        return Stage[sn][sp];
        break;
    case TextType::ManSpeak:
        return ManSpeak[sn][sp];
        break;
    case TextType::GameClear:
        return GameClear[sn][sp];
        break;
    }

    return -1;
}

// ���s���� //

void Remarks::NewLine()
{
    //���s���ĕ\���ʒu�����[����ɂ���
    textY++;
    textX = 0;
}

// �`�揈�� //

void Remarks::Draw()
{
    //�e�L�X�g�{�b�N�X�`��
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, graph);
    DrawExtendGraph((int)objPos.x, (int)objPos.y, (int)objPos.x + 1920, (int)objPos.y + 480, objHandle, TRUE);

    //�䎌�`��
    for (int i = 0; i < BUFHEIGHT; i++)
    {
        DrawString(i + 620, i * TEXTSIZE + 930, stringBuf[i], GetColor(255, 255, 255));
    }
}