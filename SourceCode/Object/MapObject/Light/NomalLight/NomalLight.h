#pragma once
#include<DxLib.h>
#include<time.h>

#include"../../../../Asset/AssetManager/AssetManager.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Collision/Collision.h"

/*Light�̃N���X*/
class Light :public ObjectBase
{
public:
	/// <summary>
	/// Light�R���X�g���N�^�[
	/// </summary>
	Light();

	/// <summary>
	/// Light�R���X�g���N�^�[
	/// </summary>
	/// <param name="LightPos">:�C�X�̃��[���h���W</param>
	Light(VECTOR LightPos,bool flash=false);


	/// <summary>
	/// Light�f�X�g���N�^�[
	/// </summary>
	~Light();

	/// <summary>
	/// Light�ǂݍ��ݏ���
	/// </summary>
	void Load();

	/// <summary>
	/// Light�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime)override;

	void Flash(float deltaTime);

	/// <summary>
	/// Light�`�揈��
	/// </summary>
	void Draw()override;

private:
	float lightBright;
	bool isFlash;
	int flashTime;
	int lightTimer;
};
