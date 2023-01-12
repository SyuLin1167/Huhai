#pragma once
#include<DxLib.h>
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/ObjectBase/ObjectBase.h"
#include"../../Asset/Animation/Animation.h"

/*Door�̃N���X*/
class Door:public ObjectBase
{
public:
	/// <summary>
	/// Door�R���X�g���N�^�[
	/// </summary>
	Door();

	/// <summary>
	/// Door�R���X�g���N�^�[
	/// </summary>
	/// <param name="doorPos">:�h�A�̃��[���h���W</param>
	Door(VECTOR doorPos);

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
	/// Door�`�揈��
	/// </summary>
	void Draw()override;
	
	typedef enum Anim
	{
		IDLE=0,			//�ҋ@
		OPEN,			//�J
		CLOSE			//��
	};
private:
	//---�A�j���[�V�����֘A---//
	class Animation* doorAnim;			//�A�j���[�V����
	int animType;						//�A�j���[�V�������
};

