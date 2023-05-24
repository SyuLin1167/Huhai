#pragma once
#include<random>
#include<time.h>

#include"../LightBase/LightBase.h"

/*BlinkingLighit�̃N���X*/
class BlinkingLight :public LightBase
{
public:
	/// <summary>
	/// BlinkingLight�R���X�g���N�^
	/// </summary>
	BlinkingLight();

	/// <summary>
	/// BlinkingLight�R���X�g���N�^
	/// </summary>
	/// <param name="lightPos">:���C�g�̃��[���h���W</param>
	BlinkingLight(VECTOR lightPos);

	/// <summary>
	/// BlinkingLight�f�X�g���N�^
	/// </summary>
	~BlinkingLight();

	/// <summary>
	/// BlinkingLight�ǂݍ��ݏ���
	/// </summary>
	void Load();

	/// <summary>
	/// BlinkingLight�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// BlinkingLight�`�揈��
	/// </summary>
	void Draw()override;

private:
	float intervalTime;
	float countTimer;
	bool lightBlinking;
};

