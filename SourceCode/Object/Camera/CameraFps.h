#pragma once
#include<DxLib.h>
#include"../ObjectBase/ObjectBase.h"
#include"../ObjectManager/ObjManager.h"

const float CameraNear = 1.0f;       //�J�����̕`��͈�(��)
const float CameraFar = 2000.0f;     //�J�����̕`��͈�(��)

/*��l�̎��_�̃N���X*/
class CameraFps:public ObjectBase
{
public:
    /// <summary>
    /// CamreFps�R���X�g���N�^�[
    /// </summary>
    /// <param name="targetPos">�J�����������W</param>
    CameraFps();

    /// <summary>
    /// CamreFps�f�X�g���N�^�[
    /// </summary>
    ~CameraFps() {};

    /// <summary>
    /// CameraFps�X�V����
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime)override;
private:
    int mouseX;
    int mouseY;
    VECTOR mousePos;
    VECTOR camLookPos;
};

