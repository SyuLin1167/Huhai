#include "PointLightShader.h"
#include<DxLib.h>

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

PointLightShader::~PointLightShader()
{
    //�V�F�[�_�[�̌㏈��
    DeleteShader(VSHandle);
    DeleteShader(PSHandle);
}