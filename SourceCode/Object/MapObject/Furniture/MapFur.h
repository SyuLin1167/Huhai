#pragma once
#include<DxLib.h>
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Asset/AssetManager/AssetManager.h"

/*MapFurのクラス*/
class MapFur :public ObjectBase
{
public:
	/// <summary>
	/// MapFurコンストラクター
	/// </summary>
	MapFur();

	/// <summary>
	/// MapFurコンストラクター(位置セット)
	/// </summary>
	/// <param name="MapFurPos">:マップのワールド座標</param>
	MapFur(VECTOR MapFurPos);

	/// <summary>
	/// MapFurデストラクター
	/// </summary>
	~MapFur();

	/// <summary>
	/// MapFurモデル読み込み処理
	/// </summary>
	void LoadModel();

	/// <summary>
	/// MapFur更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime) override;

	/// <summary>
	/// MapFur描画処理
	/// </summary>
	void Draw()override;
};

