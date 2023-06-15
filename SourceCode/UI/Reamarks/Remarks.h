#pragma once
#include"../../Object/ObjectBase/ObjectBase.h"
#include"TextType.h"

constexpr int TEXTSIZE = 24;
constexpr int BUFWIDTH = 50;
constexpr int BUFHEIGHT = 20;

        /*Remarks�̃N���X*/
class Remarks :public ObjectBase
{
public:
    /// <summary>
    /// Remarks�R���X�g���N�^
    /// </summary>
    /// <param name="texttype">:�e�L�X�g�̎��</param>
    Remarks(TextType texttype);

    /// <summary>
    /// Remarks�f�X�g���N�^
    /// </summary>
    ~Remarks();

    /// <summary>
    /// Remarks�X�V����
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
    /// Remarks�`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// Remarks�I���t���O
    /// </summary>
    /// <returns>:�I���t���O</returns>
    bool RemarksEof() { return eofFlag; }

private:
    TextType textType;
    char stringBuf[BUFHEIGHT][BUFWIDTH * 2 + 1];        //���z�e�L�X�g�o�b�t�@
    int textX;                                          //�����\���ʒuX
    int textY;                                          //�����\���ʒuY
    int Sn;                                             //������ԍ�
    int Sp;                                             //�����|�C���^
    bool eofFlag;                                       //�I���t���O
    bool waitKey;                                       //�ҋ@�t���O
    char holdBuf[3];                                    //�����ꎞ�L���̈�
    int graph;
};