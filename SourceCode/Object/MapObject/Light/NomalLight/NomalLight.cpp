#include "NomalLight.h"

NomalLight::NomalLight(std::string scene, std::string num)
    :LightBase(scene,num)
{
    //�����Ȃ�
}

NomalLight::~NomalLight()
{
    //�����Ȃ�
}


void NomalLight::Update(float deltaTime)
{
    //�p�����[�^�[�ɂ�鋗������
    AttenByParam();
}

void NomalLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}