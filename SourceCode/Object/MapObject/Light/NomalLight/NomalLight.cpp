#include "NomalLight.h"

// �R���X�g���N�^ //

NomalLight::NomalLight(std::string scene, std::string num)
    :LightBase(scene,num)
{
}
// �f�X�g���N�^ //

NomalLight::~NomalLight()
{
    //�����Ȃ�
}


// �X�V���� //

void NomalLight::Update(float deltaTime)
{
    //�p�����[�^�[�ɂ�鋗������
    AttenByParam();
}

// �`�揈�� //

void NomalLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}