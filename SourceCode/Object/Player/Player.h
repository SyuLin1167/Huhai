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
	/// �ΏۂƂ̓����蔻��
	/// </summary>
	/// <param name="target"></param>
	//void OnCollisionEnter(const ObjectBase* target)override;

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
		IDLE = 0,							//�ҋ@
		RUN,								//����
		ATACK								//�U��
	};

private:
	/// <summary>
	/// Player�ړ�����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Move(float deltaTime);

	/// <summary>
	/// Player��]����
	/// </summary>
	void Rotate();

	//---�A�j���[�V�����֘A---//
	Animation* plyAnim;						//�A�j���[�V����
	int animType;							//�A�j���[�V�������

	VECTOR UP;								//�O����
	VECTOR DOWN;							//�����
	VECTOR RIGHT;							//�E����
	VECTOR LEFT;							//������

	VECTOR inputVec;						//�����x�N�g��
	VECTOR inputVel;						//���x�x�N�g��
	VECTOR aimDir;							//�ڕW����
	bool inputKey;							//�L�[���͔���
	bool nowRoted;							//���݉�]�����ǂ���

	Sphere colSphere;						//�����蔻�苅

	//---�J�����֘A---//
	VECTOR camFront;
};