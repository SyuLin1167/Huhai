#pragma once
#include<DxLib.h>
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Asset/AssetManager/AssetManager.h"

/*Map�̃N���X*/
class Map:public ObjectBase
{
public:
	/// <summary>
	/// Map�R���X�g���N�^�[
	/// </summary>
	Map();

	/// <summary>
	/// Map�R���X�g���N�^�[(�ʒu�Z�b�g)
	/// </summary>
	/// <param name="mapPos">:�}�b�v�̃��[���h���W</param>
	Map(VECTOR mapPos);

	/// <summary>
	/// Map�f�X�g���N�^�[
	/// </summary>
	~Map();

	/// <summary>
	/// Map�ǂݍ��ݏ���
	/// </summary>
	void LoadModel();

	/// <summary>
	/// Map�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime) override;

	/// <summary>
	/// Map�`�揈��
	/// </summary>
	void Draw()override;
};

