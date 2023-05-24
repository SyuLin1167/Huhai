#pragma once
#include<map>

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"

using namespace std;

constexpr int TableNum = 2;

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
	map<int, VECTOR> posData{
	{0,{230,0,20}},
	{1,{230,0,-20}},
	};
	map<int, float> dirData{
		{0,0.0f},
		{1,90.0f},
	};
};

