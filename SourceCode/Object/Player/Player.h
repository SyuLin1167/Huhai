#pragma once
#include<DxLib.h>

#include"../ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../ObjectBase/ObjectBase.h"
#include"../../Asset/Animation/Animation.h"
#include"../../Collision/Collision.h"

class Animation;

/* Player�̃N���X */
class Player :public ObjectBase
{
	Animation* plyAnim = nullptr;				//�A�j���[�V����

public:
	/// <summary>
	/// Player�R���X�g���N�^�[
	/// </summary>
	Player();

	/// <summary>
	/// Player�f�X�g���N�^�[
	/// </summary>
	~Player();

	/// <summary>
	/// Player�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime) override;

	/// <summary>
	/// Player�`�揈��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �����蔻�苅�擾
	/// </summary>
	/// <returns>�����蔻�苅</returns>
	Sphere GetColSphere() { return colSphere; }

	/// <summary>
	/// �A�j���[�V�����X�e�[�^�X
	/// </summary>
	typedef enum Anim
	{
		IDLE = 0,						//�ҋ@
		RUN,							//����
		ATACK							//�U��
	};

private:
	VECTOR UP = { 0, 0, 0.9f };			//�O����
	VECTOR DOWN = { 0, 0, -0.9f };		//�����
	VECTOR RIGHT = { 0.9f, 0, 0 };		//�E����
	VECTOR LEFT = { -0.9f, 0, 0 };		//������

	VECTOR InputVec;					//�����x�N�g��
	bool KeyInput;						//�L�[���͔���

	Sphere colSphere;					//�����蔻�苅

	Anim animType;						//�A�j���[�V�������
};

