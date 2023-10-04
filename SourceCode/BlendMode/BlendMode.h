#pragma once

#include"../GameSetting/GameSetting.h"

/*BlendMode�N���X*/
class BlendMode
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="speed">:�t�F�[�h���x(�f�t�H���g�E80.0)</param>
    BlendMode(float speed = 80.0f);

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
    void AddFade(float deltaTime);

    /// <summary>
    /// �t�F�[�h�C��
    /// </summary>
    void SubFade(float deltaTime);

    /// <summary>
    /// �t�F�[�h�t���O
    /// </summary>
    /// <returns>�t�F�[�h��:true|�łȂ�:false</returns>
    bool NowFade() { return nowFade; }

private:
    bool nowFade;                   //�t�F�[�h�t���O
    float fadeValue;                  //�t�F�[�h�l
    float fadeSpeed;                  //�t�F�[�h���x

    bool nowDark;                   //�Ó]�t���O
    const int darkValue = 150;      //�Ó]�l
};

