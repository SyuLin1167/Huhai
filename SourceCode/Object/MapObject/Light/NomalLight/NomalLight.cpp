#include "NomalLight.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">:�V�[����</param>
/// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
NomalLight::NomalLight(std::string scene, std::string num)
    :LightBase(scene,num)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NomalLight::~NomalLight()
{
    //�����Ȃ�
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�f���^�^�C��</param>
void NomalLight::Update(float deltaTime)
{
    //�p�����[�^�[�ɂ�鋗������
    AttenByParam();
}

/// <summary>
/// �`�揈��
/// </summary>
void NomalLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}