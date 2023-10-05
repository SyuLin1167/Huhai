#pragma once
#include<random>
#include<time.h>

#include"../LightBase/LightBase.h"

        /*BlinkingLighit�N���X*/
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
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

private:
    float intervalTime;     //�C���^�[�o��
    float countTimer;       //�J�E���g
    bool isBlinking;        //�_�Ŕ���

    const float BLINK_PARAM = 0.001f;                       //�_�Œl
    const COLOR_F BLINK_COLOR = { 0.8f, 0.8f, 0.8f, 0.8f }; //�_�ŐF
};
