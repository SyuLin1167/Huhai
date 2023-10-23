#pragma once
#include<random>
#include<time.h>

#include"../LightBase/LightBase.h"

/// <summary>
/// BrinkingLight�N���X
/// </summary>
class BlinkingLight :public LightBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="scene">:�V�[����</param>
    /// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
    BlinkingLight(std::string scene, std::string num = "0");

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~BlinkingLight();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// ��������
    /// </summary>
    void LightOff();
private:
    float intervalTime;     //�C���^�[�o��
    float countTimer;       //�J�E���g
    bool isBlinking;        //�_�Ŕ���

    const float BLINK_PARAM = 0.001f;                       //�_�Œl
    const COLOR_F BLINK_COLOR = { 0.8f, 0.8f, 0.8f, 0.8f }; //�_�ŐF
};
