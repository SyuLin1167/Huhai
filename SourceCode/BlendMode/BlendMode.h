#pragma once

#include"../GameSetting/GameSetting.h"

/// <summary>
/// �X�N���[���̃u�����h
/// </summary>
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
    /// �Ó]����
    /// </summary>
    void Darken();
    
    /// <summary>
    /// �t�F�[�h�A�E�g
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void AddFade(const float deltaTime);

    /// <summary>
    /// �t�F�[�h�C��
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void SubFade(const float deltaTime);

    /// <summary>
    /// �t�F�[�h
    /// </summary>
    void Fade();

    /// <summary>
    /// �t�F�[�h�t���O
    /// </summary>
    /// <returns>�t�F�[�h��:true|�łȂ�:false</returns>
    bool NowFade() { return nowFade; }

    /// <summary>
    /// �f�t�H���g
    /// </summary>
    void NoBlend();

private:
    const int MAX_ALPHA = 250;      //�ő僿
    const int MIN_ALPHA = 0;        //�ŏ���

    bool nowFade;                   //�t�F�[�h�t���O
    float fadeValue;                //�t�F�[�h�l
    float fadeSpeed;                //�t�F�[�h���x

    bool nowDark;                   //�Ó]�t���O
    const int DARK_VALUE = 150;      //�Ó]�l
};

