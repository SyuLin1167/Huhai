#pragma once

#include"../GameSetting/GameSetting.h"

/*Wipe�N���X*/
class Wipe
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="speed">:�t�F�[�h���x(�f�t�H���g�E80.0)</param>
    Wipe(float speed = 80.0f);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Wipe();

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

    /// <summary>
    /// �A�Q
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Sleep(float deltaTime);

    /// <summary>
    /// �A�Q�`�揈��
    /// </summary>
    void SleepDraw();

private:
    bool nowFade;                   //�t�F�[�h�t���O
    float fadeValue;                  //�t�F�[�h�l
    float fadeSpeed;                  //�t�F�[�h���x

    bool nowDark;                   //�Ó]�t���O
    const int darkValue = 150;      //�Ó]�l

    int screenGraph;                //�����
    int gaussGraph;                 //�ڂ����p���
    float gaussValue;               //�ڂ����l
};

