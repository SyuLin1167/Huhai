#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Remarks.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../BlendMode/BlendMode.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
    /// <param name="type">:�e�L�X�g���</param>
Remarks::Remarks(TextType type)
    :UIBase(ObjTag::Remarks)
    , fileHandle(-1)
    , text()
    , lineCounter(0)
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
    //�t�@�C���ǂݍ���
    switch (type)
    {
    case TextType::Opening:
        fileHandle = FileRead_open("..//SourceCode/UI/Reamarks/RemarksData/Opening.txt");
        break;

    case TextType::Stage:
        fileHandle = FileRead_open("..//SourceCode/UI/Reamarks/RemarksData/Stage.txt");
        break;

    case TextType::ManSpeak:
        fileHandle = FileRead_open("..//SourceCode/UI/Reamarks/RemarksData/ManSpeak.txt");
        break;

    case TextType::GameClear:
        fileHandle = FileRead_open("..//SourceCode/UI/Reamarks/RemarksData/GameClear.txt");
        break;
    }

    //�t�@�C���f�[�^���
    while(FileRead_eof(fileHandle)==0)
    {
        FileRead_gets(text[lineCounter], sizeof(text[lineCounter]), fileHandle);
        lineCounter++;
    }
    FileRead_close(fileHandle);

    canClick = true;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Remarks::~Remarks()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
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

/// <summary>
/// ������擾����
/// </summary>
/// <param name="strnnum">:������ԍ�</param>
/// <param name="strptr">:�����|�C���^</param>
/// <returns>�w��ꏊ�̕���</returns>
char Remarks::GetText(int strnnum, int strptr)
{
    return text[strnnum][strptr];
}

/// <summary>
/// ���s����
/// </summary>
void Remarks::NewLine()
{
    //���s���ĕ\���ʒu�����[����ɂ���
    textY++;
    textX = 0;
}

/// <summary>
/// �e�L�X�g�{�b�N�X
/// </summary>
/// <param name="lx">:������W</param>
/// <param name="ly">:������W</param>
/// <param name="rx">:�E�����W</param>
/// <param name="ry">:�E�����W</param>
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

/// <summary>
/// �`�揈��
/// </summary>
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