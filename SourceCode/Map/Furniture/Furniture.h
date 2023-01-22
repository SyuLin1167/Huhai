#pragma once
#include<DxLib.h>
#include"../../Object/ObjectBase/ObjectBase.h"
#include"../../Asset/AssetManager/AssetManager.h"

/*Furniture�̃N���X*/
class Furniture :public ObjectBase
{
public:
	/// <summary>
	/// Furniture�R���X�g���N�^�[
	/// </summary>
	Furniture();

	/// <summary>
	/// Furniture�R���X�g���N�^�[(�ʒu�Z�b�g)
	/// </summary>
	/// <param name="FurniturePos">:�}�b�v�̃��[���h���W</param>
	Furniture(VECTOR FurniturePos);

	/// <summary>
	/// Furniture�f�X�g���N�^�[
	/// </summary>
	~Furniture();

	/// <summary>
	/// Furniture�ǂݍ��ݏ���
	/// </summary>
	void Load();

	/// <summary>
	/// Furniture�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime) override;

	/// <summary>
	/// Furniture�`�揈��
	/// </summary>
	void Draw()override;
};

