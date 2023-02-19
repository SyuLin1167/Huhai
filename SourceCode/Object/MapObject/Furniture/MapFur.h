#pragma once
#include<DxLib.h>
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Asset/AssetManager/AssetManager.h"

/*MapFur�̃N���X*/
class MapFur :public ObjectBase
{
public:
	/// <summary>
	/// MapFur�R���X�g���N�^�[
	/// </summary>
	MapFur();

	/// <summary>
	/// MapFur�R���X�g���N�^�[(�ʒu�Z�b�g)
	/// </summary>
	/// <param name="MapFurPos">:�}�b�v�̃��[���h���W</param>
	MapFur(VECTOR MapFurPos);

	/// <summary>
	/// MapFur�f�X�g���N�^�[
	/// </summary>
	~MapFur();

	/// <summary>
	/// MapFur���f���ǂݍ��ݏ���
	/// </summary>
	void LoadModel();

	/// <summary>
	/// MapFur�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime) override;

	/// <summary>
	/// MapFur�`�揈��
	/// </summary>
	void Draw()override;
};

