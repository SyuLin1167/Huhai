#pragma once
#include<DxLib.h>
#include"../../Object/ObjectBase/ObjectBase.h"
#include"../../Asset/AssetManager/AssetManager.h"

/*Furnitureのクラス*/
class Furniture :public ObjectBase
{
public:
	/// <summary>
	/// Furnitureコンストラクター
	/// </summary>
	Furniture();

	/// <summary>
	/// Furnitureコンストラクター(位置セット)
	/// </summary>
	/// <param name="FurniturePos">:マップのワールド座標</param>
	Furniture(VECTOR FurniturePos);

	/// <summary>
	/// Furnitureデストラクター
	/// </summary>
	~Furniture();

	/// <summary>
	/// Furniture読み込み処理
	/// </summary>
	void Load();

	/// <summary>
	/// Furniture更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime) override;

	/// <summary>
	/// Furniture描画処理
	/// </summary>
	void Draw()override;
};

