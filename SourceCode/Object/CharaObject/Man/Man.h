#pragma once

#include"../../ObjectBase/ObjectBase.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"

/*Man�̃N���X*/
class Man:public ObjectBase
{
public:
	/// <summary>
	/// Man�̃R���X�g���N�^
	/// </summary>
	Man();

	/// <summary>
	/// Man�̃f�X�g���N�^
	/// </summary>
	~Man();

	/// <summary>
	/// Man�ǂݍ��ݏ���
	/// </summary>
	void Load();

	/// <summary>
	/// Man�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// Man�`�揈��
	/// </summary>
	void Draw()override;

	void Rotate();

	enum Anim
	{
		CRYING = 0,			//�ҋ@
		DOWN,
	};

private:
	bool rotateNow;
	VECTOR aimDir;

	//---�A�j���[�V�����֘A---//
	Animation* manAnim;
	int animType;

	bool addRemarks;
};

