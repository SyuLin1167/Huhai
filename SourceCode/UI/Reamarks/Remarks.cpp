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
    , textType(type)
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

    //�t�@�C���ǂݍ���
    std::ifstream ifs("../SourceCode/UI/Remarks/RemarksData.json");

    //�t�@�C�����
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();

    canClick = true;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Remarks::~Remarks()
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
            char Moji = GetText(stringNum, stringPtr).c_str();
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
/// <param name="sn">:������ԍ�</param>
/// <param name="sp">:�����|�C���^</param>
/// <returns>�w��ꏊ�̕���</returns>
std::string Remarks::GetText(int sn, int sp)
{
    //�I�[�v�j���O
    auto& opening = doc["opening"];
    std::string Opening[][256] =
    {
        opening.GetArray()[0].GetString(),
        opening.GetArray()[1].GetString(),
        opening.GetArray()[2].GetString(),
        opening.GetArray()[3].GetString(),
        opening.GetArray()[4].GetString(),
        opening.GetArray()[5].GetString(),
    };

    //�X�e�[�W
    auto& stage = doc["stage"];
    std::string Stage[][256] =
    {
        stage.GetArray()[0].GetString(),
        stage.GetArray()[1].GetString(),
        stage.GetArray()[2].GetString(),
        stage.GetArray()[3].GetString(),
        stage.GetArray()[4].GetString(),
    };

    //�j���Z���t
    auto& manSpeak = doc["manspeak"];
    std::string ManSpeak[][256] =
    {
        manSpeak.GetArray()[0].GetString(),
        manSpeak.GetArray()[1].GetString(),
        manSpeak.GetArray()[2].GetString(),
        manSpeak.GetArray()[3].GetString(),
        manSpeak.GetArray()[4].GetString(),
        manSpeak.GetArray()[5].GetString(),
        manSpeak.GetArray()[6].GetString(),
        manSpeak.GetArray()[7].GetString(),
        manSpeak.GetArray()[8].GetString(),
        manSpeak.GetArray()[9].GetString(),
        manSpeak.GetArray()[10].GetString(),
        manSpeak.GetArray()[11].GetString(),
        manSpeak.GetArray()[12].GetString(),
        manSpeak.GetArray()[13].GetString(),
        manSpeak.GetArray()[14].GetString(),
    };

    //�N���A
    auto& clear = doc["clear"];
    std::string GameClear[][256] =
    {
        clear.GetArray()[0].GetString(),
        clear.GetArray()[1].GetString(),
        clear.GetArray()[2].GetString(),
        clear.GetArray()[3].GetString(),
        clear.GetArray()[4].GetString(),
        clear.GetArray()[5].GetString(),
        clear.GetArray()[6].GetString(),
        clear.GetArray()[7].GetString(),
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

    return "";
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