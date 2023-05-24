#pragma once
#include<map>

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"

using namespace std;

constexpr int TableNum = 2;

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
	map<int, VECTOR> posData{
	{0,{230,0,20}},
	{1,{230,0,-20}},
	};
	map<int, float> dirData{
		{0,0.0f},
		{1,90.0f},
	};
};

