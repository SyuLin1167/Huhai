#pragma once
#include<map>

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Collision/Collision.h"

using namespace std;

constexpr int TableNum = 4;

/*Table�N���X*/
class Table:public ObjectBase
{
public:
	/// <summary>
	/// Table�R���X�g���N�^
	/// </summary>
	/// <param name="objNum">:�I�u�W�F�N�g�ԍ�</param>
	Table(int objNum);

	/// <summary>
	/// Table�f�X�g���N�^
	/// </summary>
	~Table();

	/// <summary>
	/// Table�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// Table�`�揈��
	/// </summary>
	void Draw()override;

private:
	map<int, VECTOR> posData
	{
		{0,{215,0,8}},
		{1,{220,0,-21}},
		{2,{250,0,-10}},
		{3,{240,0,18}},
	};
	map<int, float> dirData
	{
		{0,0.0f},
		{1,90.0f},
		{2,0.0f},
		{3,-75.0f},
	};
};

