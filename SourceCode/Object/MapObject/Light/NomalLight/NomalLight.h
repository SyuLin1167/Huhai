#pragma once

#include"../LightBase/LightBase.h"

/// <summary>
/// �ʏ�̃��C�g
/// </summary>
class NomalLight :public LightBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="scene">:�V�[����</param>
    /// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
    NomalLight(std::string scene, std::string num = "0");


    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~NomalLight();

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
