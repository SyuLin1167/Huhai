#include "Remarks.h"

#include"../../Asset/AssetManager/AssetManager.h"
#include"../../BlendMode/BlendMode.h"

// �R���X�g���N�^ //

Remarks::Remarks(TextType texttype)
    :UIBase(ObjTag::Remarks)
    , textType(texttype)
    , stringBuf{}
    , holdBuf{}
    , stringNum(0)
    , stringPtr(0)
    , eofFlag(false)
    , waitKey(false)
    , textX(0)
    , textY(0)
    , textBox{}
{
    //�e�L�X�g�{�b�N�X�ݒ�
    objHandle =AssetManager::GetGraph("../Assets/BackGround/Remarks.png");
    objPos = VGet(0.0f, 600.0f, 0.0f);

    canClick = true;
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
            MouseClick();
            if (hasMauseClick)
            {
                waitKey = false;
            }
        }
        else
        {
            //�ҋ@���łȂ���Α䎌���ꕶ�����ǂݍ���
            char Moji = GetText(stringNum, stringPtr);
            switch (Moji)
            {
            case '/':
                //�ҋ@������������ҋ@���ɂ���
                waitKey = true;

                //�ǂݍ��ݕ�����1�����i�߂�
                stringPtr++;
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
                stringPtr++;
                break;

            default:
                //���̑��̕�����������
                //1�������L��
                holdBuf[0] = GetText(stringNum, stringPtr);
                holdBuf[1] = GetText(stringNum, stringPtr + 1);
                holdBuf[2] = '\0';

                //�e�L�X�g�o�b�t�@�ɋL��������������
                stringBuf[textY][textX * 2] = holdBuf[0];
                stringBuf[textY][textX * 2 + 1] = holdBuf[1];

                //�ǂݍ��ݕ�����2�������i�߂�
                stringPtr += 2;

                //�����\���ʒu��1�����i�߂�
                textX++;

                //�����\���ʒu����������͂ݏo������s
                if (textX > BUFWIDTH)
                {
                    NewLine();
                }

                //�����Ō�܂œǂݍ��ݏI���������s���Ď��̕���ǂݍ���
                if (GetText(stringNum, stringPtr) == '\0')
                {
                    NewLine();
                    stringNum++;
                    stringPtr = 0;
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
        "/�����ƍȂƐG�ꍇ���Ă���Ηǂ������ƁA/�S��v���B ",
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
        "/|�j���u�Ƃɂ������c���瓦���؂�񂾁B ",
        "/��������΁A�A�C�c�����������B�v ",
        "/|�j���u....!?/�܂����A�A�C�c������! /���͂��������܂ł��A ",
        "/���C�g����邩��A�����������瓦�����!�v ",
        "/^ ",
    };

    //�N���A
    char GameClear[][256] =
    {
        "���𔲂���Ƃ��A�Ȃ̐������������C�������B ",
        "/������������A�����Ƃ��΂ɂ��Ă���Ă����̂�������Ȃ��B ",
        "/|���̖�����A�����͑�؂Ȃ��ƂɋC�t�����񂾁B",
        "/|�u���肪�Ƃ��A/������l�ł����v����B ",
        "/������ɍs���܂�/������Ă��Ăق����B�v ",
        "/|���ꂩ��A/�����܂ŏ[���������X�𑗂邱�Ƃ��o���Ă���B ",
        "/|�N�����΂ɂ��Ă��ꂽ����A/�����Ǝx���Ă��ꂽ����...�B  ",
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

// �e�L�X�g�{�b�N�X //
void Remarks::TextBox(int lx, int ly, int rx, int ry)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    //�l���ς��Ȃ����̂���ʂ�ݒ�
    for (int i = 0; i < 6; i++)
    {
        textBox[i].pos.z = 0.0f;
        textBox[i].rhw = 1.0f;
        textBox[i].dif = VERTEX_COLOR;
        textBox[i].u = UV;
        textBox[i].v = UV;
    }


    //���_���
    textBox[0].pos.x = textBox[2].pos.x = (float)lx;
    textBox[0].pos.y = textBox[1].pos.y = (float)ly;

    textBox[3].pos.x = textBox[1].pos.x = (float)rx;
    textBox[3].pos.y = textBox[2].pos.y = (float)ry;
    textBox[3].dif.a = textBox[2].dif.a = 255;

    //�������_�̓R�s�[
    textBox[4] = textBox[2];
    textBox[5] = textBox[1];

}

// �`�揈�� //

void Remarks::Draw()
{
    ChangeFont("MS �S�V�b�N", DX_CHARSET_DEFAULT);

    //�e�L�X�g�{�b�N�X�`��
    SetFontSize(TEXTSIZE);
    DrawBox(0, BOUNDARY_POS_RY, SCREEN_WIDTH, SCREEN_HEIGHT, TEXTBOX_COLOR, TRUE);
    TextBox(0, BOUNDARY_POS_LY, SCREEN_WIDTH, BOUNDARY_POS_RY);
    DrawPolygon2D(textBox, 2, DX_NONE_GRAPH, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    //�䎌�`��
    for (int i = 0; i < BUFHEIGHT; i++)
    {
        DrawString(i + FIRST_TEXT_POS_X, i * TEXTSIZE + FIRST_TEXT_POS_Y, stringBuf[i], WHITE_TEXT_COLOR);
    }

    //�ҋ@�A�C�R���`��
    if (waitKey)
    {
        DrawString(WAIT_ICON_X, WAIT_ICON_Y, "��", WHITE_TEXT_COLOR);
    }
}