#pragma once

#include"../../../../GameSetting/GameSetting.h"
#include"../../../ObjectBase/ObjectBase.h"

constexpr float CameraNear = 0.1f;       //�J�����̕`��͈�(��)
constexpr float CameraFar = 400.0f;     //�J�����̕`��͈�(��)

constexpr float CameraPosY = 22.5f;

/*FpsCamera�N���X*/
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
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// �ړ�����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Move(float deltaTime);

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;
private:
    int mouseX;             //�}�E�X���WX
    int mouseY;             //�}�E�X���WY
    VECTOR movePos;         //�ړ����W

    float cameraYaw;        //����������]�p
    float cameraPitch;      //����������]�p
};
