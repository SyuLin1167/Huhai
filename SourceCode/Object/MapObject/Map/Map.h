#pragma once
#include<DxLib.h>
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Asset/AssetManager/AssetManager.h"

/*Mapのクラス*/
class Map:public ObjectBase
{
public:
	/// <summary>
	/// Mapコンストラクター
	/// </summary>
	Map();

	/// <summary>
	/// Mapコンストラクター(位置セット)
	/// </summary>
	/// <param name="mapPos">:マップのワールド座標</param>
	Map(VECTOR mapPos);

	/// <summary>
	/// Mapデストラクター
	/// </summary>
	~Map();

	/// <summary>
	/// Map読み込み処理
	/// </summary>
	void LoadModel();

	/// <summary>
	/// Map更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime) override;

	/// <summary>
	/// Map描画処理
	/// </summary>
	void Draw()override;
};

