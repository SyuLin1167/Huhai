#pragma once
#include"../LightBase/LightBase.h"

/// <summary>
/// FlashLight�N���X
/// </summary>
class FlashLight :public LightBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FlashLight();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FlashLight();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;
};
