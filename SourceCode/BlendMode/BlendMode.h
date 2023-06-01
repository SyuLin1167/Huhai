#pragma once
#include<DxLib.h>

/*BlendMode�̃N���X*/
class BlendMode
{
public:
    /// <summary>
    /// BlendMode�R���X�g���N�^
    /// </summary>
    BlendMode(int fadespeed = 4);

    /// <summary>
    /// BlendMode�f�X�g���N�^
    /// </summary>
    ~BlendMode();

    /// <summary>
    /// �t�F�[�h
    /// </summary>
    void Fade();

    /// <summary>
    /// �Ó]����
    /// </summary>
    void Darken();

    /// <summary>
    /// �f�t�H���g
    /// </summary>
    void NoBlend();

    /// <summary>
    /// �t�F�[�h���Z
    /// </summary>
    void AddFade();

    /// <summary>
    /// �t�F�[�h���Z
    /// </summary>
    void SubFade();

    /// <summary>
    /// �t�F�[�h�t���O
    /// </summary>
    /// <returns>:�t�F�[�h�����ǂ���</returns>
    bool NowFade() { return nowFade; }

private:


    bool nowFade;                           //fade�t���O
    int fadeValue;                          //fade�l
    int fadeSpeed;                //fade���x

    bool nowDark;                           //dark�t���O
    const int darkValue = 150;              //dark�l

    static BlendMode* blend;                //BlendMode�̎���
};

