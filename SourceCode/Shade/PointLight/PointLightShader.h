#pragma once

/// <summary>
/// PointLIghtShader�N���X
/// </summary>
class PointLightShader
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PointLightShader();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PointLightShader();

private:
    int VSHandle;       //���_�V�F�[�_�[�n���h��
    int PSHandle;       //�s�N�Z���V�F�[�_�[�n���h��

};

