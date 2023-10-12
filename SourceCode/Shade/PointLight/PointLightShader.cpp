#include "PointLightShader.h"
#include<DxLib.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
PointLightShader::PointLightShader()
{
    //�V�F�[�_�[�ǂݍ���
    VSHandle = LoadVertexShader("../SourceCode/Shade/PointLight/PointLightVS.vso");
    PSHandle = LoadPixelShader("../SourceCode/Shade/PointLight/PointLightPS.pso");

    //�V�F�[�_�[�ݒ�
    MV1SetUseOrigShader(true);
    SetUseVertexShader(VSHandle);
    SetUsePixelShader(PSHandle);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PointLightShader::~PointLightShader()
{
    //�V�F�[�_�[�̌㏈��
    DeleteShader(VSHandle);
    DeleteShader(PSHandle);
}