#pragma once
#include<DxLib.h>
#include"../ObjectBase/ObjectBase.h"
#include"../ObjectManager/ObjManager.h"

const float CameraNear = 1.0f;       //�J�����̕`��͈�(��)
const float CameraFar = 200.0f;     //�J�����̕`��͈�(��)

/*��l�̎��_�̃N���X*/
class CameraFps:public ObjectBase
{
public:
    /// <summary>
    /// CamreFps�R���X�g���N�^�[
    /// </summary>
    CameraFps();

    /// <summary>
    /// CamreFps�f�X�g���N�^�[
    /// </summary>
    ~CameraFps() {};

    /// <summary>
    /// CameraFps�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// CameraFps�ړ�����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Move(float deltaTime);

private:
    //---�}�E�X�֘A---//
    int mouseX;             //�}�E�X���WX
    int mouseY;             //�}�E�X���WY
    VECTOR movePos;         //�ړ����W

    //---�J���������֘A---//
    float cameraYaw;        //����������]�p
    float cameraPitch;      //����������]�p
    VECTOR camLookPos;      //�����_
};

