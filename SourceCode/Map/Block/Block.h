#pragma once
#include<DxLib.h>
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/ObjectBase/ObjectBase.h"

class Block :public ObjectBase
{
public:
	/// <summary>
	/// Block�R���X�g���N�^�\
	/// </summary>
	Block();

	/// <summary>
	/// Block�R���X�g���N�^�\
	/// </summary>
	/// <param name="pos">:�u���b�N�̃��[���h���W</param>
	Block(VECTOR blkPos);

	/// <summary>
	/// Block�f�X�g���N�^�\
	/// </summary>
	~Block();

	/// <summary>
	/// Block�ǂݍ��ݏ���
	/// </summary>
	void Load();

	/// <summary>
	/// Block�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime);
	
	/// <summary>
	/// Block�`�揈��
	/// </summary>
	void Draw();
};

