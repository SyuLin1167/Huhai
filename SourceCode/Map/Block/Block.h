#pragma once
#include<DxLib.h>
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/ObjectBase/ObjectBase.h"

class Block :public ObjectBase
{
public:
	/// <summary>
	/// Blockコンストラクタ―
	/// </summary>
	Block();

	/// <summary>
	/// Blockコンストラクタ―
	/// </summary>
	/// <param name="pos">:ブロックのワールド座標</param>
	Block(VECTOR blkPos);

	/// <summary>
	/// Blockデストラクタ―
	/// </summary>
	~Block();

	/// <summary>
	/// Block読み込み処理
	/// </summary>
	void Load();

	/// <summary>
	/// Block更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime);
	
	/// <summary>
	/// Block描画処理
	/// </summary>
	void Draw();
};

