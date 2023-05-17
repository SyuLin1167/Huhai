#pragma once
#include<random>
#include<time.h>

#include"../LightBase/LightBase.h"

/*FlashLighit�̃N���X*/
class FlashLight:public LightBase
{
public:
	/// <summary>
	/// FlashLight�R���X�g���N�^
	/// </summary>
	FlashLight();

	/// <summary>
	/// FlashLight�R���X�g���N�^
	/// </summary>
	/// <param name="lightPos">:���C�g�̃��[���h���W</param>
	FlashLight(VECTOR lightPos);

	/// <summary>
	/// FlashLight�f�X�g���N�^
	/// </summary>
	~FlashLight();

	/// <summary>
	/// FlashLight�ǂݍ��ݏ���
	/// </summary>
	void Load();

	/// <summary>
	/// FlashLight�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// FlashLight�`�揈��
	/// </summary>
	void Draw()override;

private:
	float intervalTime;
	float countTimer;
	bool lightFlash;
};

