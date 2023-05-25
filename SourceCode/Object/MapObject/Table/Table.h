#pragma once
#include<map>

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Collision/Collision.h"

using namespace std;

constexpr int TableNum = 4;

/*Tableクラス*/
class Table:public ObjectBase
{
public:
	/// <summary>
	/// Tableコンストラクタ
	/// </summary>
	/// <param name="objNum">:オブジェクト番号</param>
	Table(int objNum);

	/// <summary>
	/// Tableデストラクタ
	/// </summary>
	~Table();

	/// <summary>
	/// Table更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// Table描画処理
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

