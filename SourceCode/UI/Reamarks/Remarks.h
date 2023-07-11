#pragma once

#include"../../GameSetting/GameSetting.h"
#include"../UIBase/UIBase.h"
#include"TextType.h"

constexpr int TEXTSIZE = 24;        //�e�L�X�g�T�C�Y
constexpr int BUFWIDTH = 50;        //�\�������s
constexpr int BUFHEIGHT = 20;       //�\��������

/*Remarks�N���X*/
class Remarks :public UIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="type">:�e�L�X�g�̎��</param>
    Remarks(TextType type);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Remarks();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// ������擾����
    /// </summary>
    /// <param name="sn">:������ԍ�</param>
    /// <param name="sp">:�����|�C���^</param>
    /// <returns>�w��ꏊ�̕���</returns>
    char GetText(int sn, int sp);

    /// <summary>
    /// ���s����
    /// </summary>
    void NewLine();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// �I���t���O
    /// </summary>
    /// <returns>:�I������:true|���Ȃ�:false</returns>
    bool RemarksEof() { return eofFlag; }

private:
    TextType textType;
    char stringBuf[BUFHEIGHT][BUFWIDTH * 2 + 1];        //���z�e�L�X�g�o�b�t�@
    char holdBuf[3];                                    //�����ꎞ�L���̈�
    int Sn;                                             //������ԍ�
    int Sp;                                             //�����|�C���^

    bool eofFlag;                                       //�I���t���O
    bool waitKey;                                       //�ҋ@�t���O

    int textX;                                          //�����\���ʒuX
    int textY;                                          //�����\���ʒuY

    int screenGraph;                                    //�e�L�X�g�{�b�N�X�p�X�N���[��
};