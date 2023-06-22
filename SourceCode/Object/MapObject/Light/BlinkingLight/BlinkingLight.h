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
    BlinkingLight();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">:���[���h���W</param>
    BlinkingLight(VECTOR pos);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~BlinkingLight();

    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    void Load();

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
};
