#pragma once

#include"../../../../GameSetting/GameSetting.h"
#include"../../../ObjectBase/ObjBase.h"

constexpr float CameraNear = 0.1f;       //�J�����̕`��͈�(��)
constexpr float CameraFar = 400.0f;      //�J�����̕`��͈�(��)

constexpr float CameraPosY = 22.5f;      //�J�����̍���

/// <summary>
/// FpsCamera�N���X
/// </summary>
class FpsCamera :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FpsCamera();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FpsCamera();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;
private:
    /// <summary>
    /// �ړ�����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Move(const float deltaTime);

    const float CONTROL_SENSI = 255;          //���x����p

    int mouseX;                             //�}�E�X���WX
    int mouseY;                             //�}�E�X���WY
    VECTOR movePos;                         //�ړ����W
    const int MIN_MOVE_PARAM = 30;          //�ŏ��ړ���

    float cameraYaw;                        //����������]�p
    float cameraPitch;                      //����������]�p
};
