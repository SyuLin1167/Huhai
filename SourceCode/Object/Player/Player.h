#pragma once
#include<DxLib.h>

#include"../ObjectManager/ObjManager.h"
#include"../ObjectBase/ObjectBase.h"
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
	/// ���̂̏Փˎ�����
	/// </summary>
	/// <param name="colmodel">:�����蔻�胂�f��</param>
	void CollHitSphere(int colmodel);

	/// <summary>
	/// �����̏Փˎ�����
	/// </summary>
	/// <param name="colmodel">:�����蔻�胂�f��</param>
	void ColHitLine(int colmodel);

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

	VECTOR UP = { 0,0,0 };					//�O����
	VECTOR DOWN = { 0,0,0 };				//�����
	VECTOR RIGHT = { 0,0,0 };				//�E����
	VECTOR LEFT = { 0,0,0 };				//������

	VECTOR inputVec;						//�����x�N�g��
	VECTOR inputVel;						//���x�x�N�g��
	VECTOR aimDir;							//�ڕW����
	bool inputKey;							//�L�[���͔���
	bool nowRoted;							//���݉�]�����ǂ���

	//---�����蔻��֘A---//
	Sphere colSphere;			//�����蔻�苅

	//---�J�����֘A---//
	VECTOR camFront;						//�J�����O����
};