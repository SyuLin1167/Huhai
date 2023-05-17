#pragma once
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Collision/Collision.h"

/*Chair�̃N���X*/
class Chair:public ObjectBase
{
public:
	/// <summary>
	/// Chair�R���X�g���N�^�[
	/// </summary>
	Chair();

	/// <summary>
	/// Chair�f�X�g���N�^�[
	/// </summary>
	~Chair();

	/// <summary>
	/// Chair�ǂݍ��ݏ���
	/// </summary>
	void Load();

	/// <summary>
	/// Chair�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// Chair�`�揈��
	/// </summary>
	void Draw()override;

	enum Anim
	{
		IDLE = 0,			//�ҋ@
		MOVE,
	};
private:
	//---�A�j���[�V�����֘A---//
	class Animation* ChairAnim;			//�A�j���[�V����
	int animType;						//�A�j���[�V�������
};

