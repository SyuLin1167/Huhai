#pragma once
#include<DxLib.h>

#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Collision/Collision.h"

/*Door�̃N���X*/
class Door:public ObjectBase
{
	ObjectBase* player;
public:
	/// <summary>
	/// Door�R���X�g���N�^�[
	/// </summary>
	Door();

	/// <summary>
	/// Door�R���X�g���N�^�[
	/// </summary>
	/// <param name="doorPos">:�h�A�̃��[���h���W</param>
	/// <param name="doorAngle">:�h�A�̕���</param>
	Door(VECTOR doorPos,VECTOR doorAngle);

	/// <summary>
	/// Door�f�X�g���N�^�[
	/// </summary>
	~Door();
	
	/// <summary>
	/// Door�ǂݍ��ݏ���
	/// </summary>
	void Load();
	
	/// <summary>
	/// Door�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// Door�A�j���[�V��������
	/// </summary>
	/// <param name="animtype">:�A�j���[�V�����^�C�v</param>
	void MoveAnim(int animtype);

	/// <summary>
	/// Door�`�揈��
	/// </summary>
	void Draw()override;
	
	enum Anim
	{
		IDLE=0,			//�ҋ@
		OPEN,			//�J
		CLOSE			//��
	};
private:
	//---�A�j���[�V�����֘A---//
	class Animation* doorAnim;			//�A�j���[�V����
	int animType;						//�A�j���[�V�������

	class Model* doorModel;

	class Sound* doorSound;
};

