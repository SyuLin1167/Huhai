#pragma once
#include<DxLib.h>

#include"../ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../ObjectBase/ObjectBase.h"
#include"../../Asset/Animation/Animation.h"
#include"../../Collision/Collision.h"

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
	/// Player�Փˎ�����
	/// </summary>
	/// <param name="other">:�I�u�W�F�N�g</param>
	void OnCollisionEnter(const ObjectBase* other)override;

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
	class Animation* plyAnim;				//�A�j���[�V����
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

	//---�����蔻��֘A---//
	class Collision* plyCol;				//�R���W����
	Collision::Sphere colSphere;			//�����蔻�苅

	//---�J�����֘A---//
	VECTOR camFront;						//�J�����O����
};