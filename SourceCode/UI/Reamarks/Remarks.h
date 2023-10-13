#pragma once

#include"../../GameSetting/GameSetting.h"
#include"../UIBase/UIBase.h"
#include"TextType.h"

constexpr int TEXTSIZE = 24;        //�e�L�X�g�T�C�Y
constexpr int BUFWIDTH = 50;        //�\�������s
constexpr int BUFHEIGHT = 20;       //�\��������

/// <summary>
/// Remarks�N���X
/// </summary>
class Remarks :public UIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="type">:�e�L�X�g���</param>
    Remarks(TextType type);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Remarks();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// ������擾����
    /// </summary>
    /// <param name="strnnum">:������ԍ�</param>
    /// <param name="strptr">:�����|�C���^</param>
    /// <returns>�w��ꏊ�̕���</returns>
    char GetText(int strnum, int strptr);

    /// <summary>
    /// ���s����
    /// </summary>
    void NewLine();

    /// <summary>
    /// �e�L�X�g�{�b�N�X
    /// </summary>
    /// <param name="lx">:������W</param>
    /// <param name="ly">:������W</param>
    /// <param name="rx">:�E�����W</param>
    /// <param name="ry">:�E�����W</param>
    void TextBox(int lx,int ly,int rx,int ry);

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// �I���t���O
    /// </summary>
    /// <returns>:�I������:true|���Ȃ�:false</returns>
    bool RemarksEof() { return eofFlag; }

private:
    int fileHandle;                                     //�t�@�C���n���h��
    char text[256][256];                              //�e�L�X�g
    int lineCounter;                                    //�s�J�E���^�[

    char stringBuf[BUFHEIGHT][BUFWIDTH * 2 + 1];        //���z�e�L�X�g�o�b�t�@
    char holdBuf[3];                                    //�����ꎞ�L���̈�
    int stringNum;                                      //������ԍ�
    int stringPtr;                                      //�����|�C���^

    const int WHITE_TEXT_COLOR= GetColor(240, 240, 240);//�e�L�X�g�F(�z���C�g)
    const int WAIT_ICON_X = SCREEN_WIDTH * 8 / 10;      //�ҋ@�A�C�R�����WX
    const int WAIT_ICON_Y = SCREEN_HEIGHT * 9 / 10;     //�ҋ@�A�C�R�����WY

    bool eofFlag;                                       //�I���t���O
    bool waitKey;                                       //�ҋ@�t���O

    const int FIRST_TEXT_POS_X = 620;                   //�e�L�X�g�������WX
    const int FIRST_TEXT_POS_Y = 930;                   //�e�L�X�g�������WY
    int textX;                                          //�����\���ʒuX
    int textY;                                          //�����\���ʒuY

    VERTEX2D textBox[6];                                //�e�L�X�g�{�b�N�X�|���S��
    const int BOUNDARY_POS_LY = 750;                    //�|���S���ƃ{�b�N�X�̋��E��������W
    const int BOUNDARY_POS_RY = 950;                    //�|���S���ƃ{�b�N�X�̋��E���E�����W
    const float UV = 0;                                 //uv
    COLOR_U8 VERTEX_COLOR = { 20,0,0,0 };               //���_�̐F
    const int TEXTBOX_COLOR = GetColor(0, 0, 20);       //�e�L�X�g�{�b�N�X�̐F
};