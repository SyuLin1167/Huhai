#pragma once
#include<DxLib.h>

    /*BlendMode�̃N���X*/
class BlendMode
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="FadeSpeed">:�t�F�[�h���x</param>
    BlendMode(int FadeSpeed = 4);

    /// <summary>
    /// �f�X�g���N�^
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
    /// �t�F�[�h�A�E�g
    /// </summary>
    void AddFade();

    /// <summary>
    /// �t�F�[�h�C��
    /// </summary>
    void SubFade();

    /// <summary>
    /// �t�F�[�h�t���O
    /// </summary>
    /// <returns>�t�F�[�h��:true|�łȂ�:false</returns>
    bool NowFade() { return nowFade; }

private:
    bool nowFade;                   //�t�F�[�h�t���O
    int fadeValue;                  //�t�F�[�h�l
    int fadeSpeed;                  //�t�F�[�h���x

    bool nowDark;                   //�Ó]�t���O
    const int darkValue = 150;      //�Ó]�l
};

