#include "Remarks.h"

        // @brief Remarks�R���X�g���N�^ //

Remarks::Remarks(TextType texttype)
    :ObjectBase(ObjectTag::Remarks)
    , textType(texttype)
    , stringBuf()
    , textX(0)
    , textY(0)
    , Sn(0)
    , Sp(0)
    , eofFlag(false)
    , waitKey(false)
    , holdBuf()
    , graph(MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT))
{
    SetFontSize(TEXTSIZE);          //�t�H���g�T�C�Y�ݒ�
    objHandle = LoadGraph("../Assets/BackGround/Remarks.png");
    objPos = VGet(0.0f, 600.0f, 0.0f);
}

        // @brief Remarks�f�X�g���N�^ //

Remarks::~Remarks()
{

}

        // @brief Remarks�X�V���� //

void Remarks::Update(float deltaTime)
{
    //�`�I���t���O�������Ă��Ȃ�������`
    if (!eofFlag)
    {
        if (waitKey)        //�`�ҋ@�t���O�������Ă�����`
        {
            //�`�}�E�X�̍��N���b�N�������ꂽ��`
            if ((GetMouseInput() & MOUSE_INPUT_LEFT))
            {
                waitKey = false;                                                    //�ҋ@�t���O��false�ɂ���
            }
        }
        else        //�`�ҋ@�t���O�������Ă��Ȃ�������`
        {
            char Moji = GetText(Sn, Sp);                                            //1�������擾
            switch (Moji)
            {
            case '/':                //�`�ҋ@������������`
                waitKey = true;                                                     //�ҋ@�t���O�𗧂Ă�
                Sp++;                                                               //�ǂݍ��ݕ�����1�����i�߂�
                break;
            case '^':                //�`�I��������������`
                eofFlag = true;                                                     //�I���t���O�𗧂Ă�
                Sp++;                                                               //�ǂݍ��ݕ�����1�����i�߂�
                break;
            case '|':                //�`�N���A������������`
                for (int i = 0; i < BUFHEIGHT; i++)
                {
                    for (int j = 0; j < BUFWIDTH; j++)
                    {
                        stringBuf[i][j] = 0;                                        //���z�e�L�X�g�o�b�t�@��������
                    }
                }
                textX = 0;                                                          //�`��ʒuX������
                textY = 0;                                                          //�`��ʒuY������
                Sp++;                                                               //�ǂݍ��ݕ�����1�����i�߂�
                break;
            default:                //�`���̑��̕����`
                //---1�������L������---//
                holdBuf[0] = GetText(Sn, Sp);
                holdBuf[1] = GetText(Sn, Sp + 1);
                holdBuf[2] = '\0';

                //---�e�L�X�g�o�b�t�@�ɑ��---//
                stringBuf[textY][textX * 2] = holdBuf[0];
                stringBuf[textY][textX * 2 + 1] = holdBuf[1];

                Sp += 2;                                                            //�ǂݍ��ݕ�����2�����i�߂�
                textX++;                                                            //�����\���ʒu��1�����i�߂�

                //�`�����\���ʒu����������͂ݏo����`
                if (textX > BUFWIDTH)
                {
                    NewLine();                                                      //���s����
                }

                //�`�ǂݍ��ݕ������I�[�܂ōs������`
                if (GetText(Sn, Sp) == '\0')
                {
                    NewLine();                                                      //���s����
                    Sn++;                                                           //�ǂݍ��ݕ�����1��i�߂�
                    Sp = 0;                                                         //�ǂݍ��ݕ��������߂���ɂ���
                }
                break;
            }
        }
    }
    if (eofFlag)
    {
        isAlive = false;
    }
}

        // @brief ������擾���� //

char Remarks::GetText(int sn, int sp)
{
    char Opening[][256] =
    {
        "�ŋߎd�������܂������Ȃ�...�B ",
        "/|�����������x���Ă��ꂽ�Ȃ����̂Ŗ������A ",
        "���ꂩ�炸���ƁA�����̐�����Ӗ������o���Ȃ��ł���B ",
        "/�����ƍȂƐG�ꍇ���Ă���Ηǂ������ƁA/�S��v���B",
        "/|�����Ǝ��́A���̎��̎��������ƈ��������Ă���̂��낤...�B ",
        "/^",
    };
    char Day1Stage[][256] =
    {
        "�����͈��...�B ",
        "/�������܂Ŏ����ŐQ�Ă����͂�����? ",
        "/|���ɂ��Ă͊��o���������肵�Ă���...�B ",
        "/|�C�����������A�i�ނ����Ȃ��̂��낤��? ",
        "/^ ",
    };
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
    char GameClear[][256] =
    {
        "���݃v���C�ł���̂͂����܂łɂȂ�܂��B",
        "/|�V��ł����������肪�Ƃ��������܂���!!!",
        "/^",
    }
    ;
    switch (textType)
    {
        //�`TextType��OpeningText��������`
    case TextType::OpeningText:
        return Opening[sn][sp];                                                     //Opening�̕������Ԃ�
        break;
        //�`TxtType��Day1Stage��������`
    case TextType::Day1Stage:
        return Day1Stage[sn][sp];
        break;
        //�`TxtType��ManSpeak��������`
    case TextType::ManSpeak:
        return ManSpeak[sn][sp];
        break;
        //�`TxtType��GameClear��������`
    case TextType::GameClear:
        return GameClear[sn][sp];
        break;
    }

    return -1;
}

        // @brief ���s���� //

void Remarks::NewLine()
{
    textY++;                                                                        //�����\�����1��i�߂�
    textX = 0;                                                                      //�����\���ʒu�������ʒu�ɂ���

    //�`�ǂݍ��ݕ����̗񂪏c������͂ݏo��Ȃ�`
    if (textY >= BUFHEIGHT)
    {
        for (int i = 1; i < BUFHEIGHT; i++)
        {
            for (int j = 0; j < BUFWIDTH * 2; j++)
            {
                stringBuf[i - 1][j] = stringBuf[i][j];                              //�e�L�X�g�o�b�t�@���c�X�N���[������
            }
        }

        textY--;                                                                    //�����\�����1����炷
    }
}

        // @brief Remarks�`�揈�� //

void Remarks::Draw()
{
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, graph);
    DrawExtendGraph((int)objPos.x, (int)objPos.y, (int)objPos.x + 1920, (int)objPos.y + 480, objHandle, TRUE);
    for (int i = 0; i < BUFHEIGHT; i++)
    {
        DrawString(i + 620, i * TEXTSIZE + 930, stringBuf[i], GetColor(255, 255, 255));     //�e�L�X�g�o�b�t�@�̕`��
    }
}