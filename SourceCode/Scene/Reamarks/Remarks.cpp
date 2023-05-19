#include "Remarks.h"


// @brief Remarks�R���X�g���N�^ //

Remarks::Remarks(TextType texttype)
    :ObjectBase(ObjectTag::UI)
    ,textType(texttype)
    ,stringBuf()
    ,textX(0)
    ,textY(0)
    ,Sn(0)
    ,Sp(0)
    ,eofFlag(false)
    ,waitKey(false)
    ,holdBuf()
{
    SetFontSize(TEXTSIZE);          //�t�H���g�T�C�Y�ݒ�
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
        //�`�ҋ@�t���O�������Ă�����`
        if (waitKey)
        {
            //�`�}�E�X�̍��N���b�N�������ꂽ��`
            if ((GetMouseInput() & MOUSE_INPUT_LEFT))
            {
                waitKey = false;                                                    //�ҋ@�t���O��false�ɂ���
            }
        }
        //�`�ҋ@�t���O�������Ă��Ȃ�������`
        else
        {
            char Moji = GetText(Sn, Sp);                                            //1�������擾
            switch (Moji)
            {
                //�`�ҋ@������������`
            case '/':
                waitKey = true;                                                     //�ҋ@�t���O�𗧂Ă�
                Sp++;                                                               //�ǂݍ��ݕ�����1�����i�߂�
                break;

                //�`�I��������������`
            case '^':
                eofFlag = true;                                                     //�I���t���O�𗧂Ă�
                Sp++;                                                               //�ǂݍ��ݕ�����1�����i�߂�
                break;

                //�`�N���A������������`
            case '|':
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

                //�`���̑��̕����`
            default:
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

char Remarks::GetText(int sn,int sp)
{
    char Opening[][256] =
    {
        "�ŋߎd�������܂������Ȃ�...�B /",
        "|�����������x���Ă��ꂽ�Ȃ����̂Ŗ������A",
        "���ꂩ�炸���ƁA�����̐�����Ӗ������o���Ȃ��ł���B/",
        "�����ƍȂƐG�ꍇ���Ă���Ηǂ������ƁA/�S��v���B/",
        "|�����Ǝ��́A���̎��̎��������ƈ��������Ă���̂��낤...�B /^",
    };
    char Day1Stage[][256] =
    {
        "�����͈��...�B /",
        "�������܂Ŏ����ŐQ�Ă����͂�����? /",
        "|���ɂ��Ă͊��o���������肵�Ă���...�B /",
        "|�C�����������A�i�ނ����Ȃ��̂��낤��? /^",
    };
    char ManSpeak[][256] =
    {
        "���Ȃ��u�Ȃ��A/�����ŉ������Ă���?/�����͈�̉��Ȃ񂾁H�v/",
        "|�j���u...�B�v/",
        "|�j���u�����́A/�ߋ��Ɏ����Ă�����̂��W�܂�ꏊ����B/�v",
        "|���Ȃ��u...?/�ǂ������Ӗ��Ȃ�?/��J�ł���Ȗ������Ă���Ă��Ƃ�?�v/",
        "|�j���u�����ɂ͉ߋ��̂����őO�ɐi�߂Ȃ��l���悭�Ă΂��B/�������c���Ă�ł�񂾂Ɖ��͎v���B�v/",
        "|���Ȃ��u���c?�v",
        "|�j���u���ɂ͎��Ԃ��Ȃ��A/���c�ɕ߂܂��Ă��܂�������ȁB/",
        "���c�ɂ��܂��Ė�����o�߂�ƁA/�����ɂ͊F��̎��𐋂��Ă���B�v/",
        "|���Ȃ��u...�悭�킩��Ȃ��A��̂ǂ�����΂���?�v/",
        "|�j���u3���ԁA/�Ƃɂ������c���瓦���؂��...�B/",
        "....!?/���c������!/���͂��������܂ł��A�����������痣����!�v/",
        "|���Ȃ��u�Ƃɂ���������΂����񂾂�?/�킩����...�B�v/",
        "�����͖��̂͂��Ȃ̂ɁA/�Ȃ������̒j���̌����ʂ�ɂ��Ȃ���΂����Ȃ��C�������B/^",
    };

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
    for (int i = 0; i < BUFHEIGHT; i++)
    {
        DrawString(i + 500, i * TEXTSIZE + 500, stringBuf[i], GetColor(255, 255, 255));     //�e�L�X�g�o�b�t�@�̕`��
    }
}