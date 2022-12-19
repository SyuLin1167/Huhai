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
	/// �����蔻�苅�擾
	/// </summary>
	/// <returns>�����蔻�苅</returns>
	Sphere GetColSphere() { return colSphere; }

	/// <summary>
	/// Camera�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void CameraUpdate(float deltTime);

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
	VECTOR UP;								//�O����
	VECTOR DOWN;							//�����
	VECTOR RIGHT;							//�E����
	VECTOR LEFT;							//������

	VECTOR InputVec;						//�����x�N�g��
	bool KeyInput;							//�L�[���͔���

	Sphere colSphere;						//�����蔻�苅

	//---�A�j���[�V�����֘A---//
	Animation* plyAnim;						//�A�j���[�V����
	Anim animType;							//�A�j���[�V�������

	//---�J�����֘A---//
	VECTOR cameraPos;						//�J�����ʒu
	VECTOR cameraFront;						//�J�������ʕ���
	const float cameraRotSpeed;				//�J������]���x
	const float cameraRad;					//�J������]���a
	float cameraYaw;						//����������]�p
};