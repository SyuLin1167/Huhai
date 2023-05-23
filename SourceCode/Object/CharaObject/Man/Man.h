#pragma once

#include"../../ObjectBase/ObjectBase.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"

/*Manのクラス*/
class Man:public ObjectBase
{
public:
	/// <summary>
	/// Manのコンストラクタ
	/// </summary>
	Man();

	/// <summary>
	/// Manのデストラクタ
	/// </summary>
	~Man();

	/// <summary>
	/// Man読み込み処理
	/// </summary>
	void Load();

	/// <summary>
	/// Man更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// Man描画処理
	/// </summary>
	void Draw()override;

	void Rotate();

	enum Anim
	{
		CRYING = 0,			//待機
		DOWN,
	};

private:
	bool rotateNow;
	VECTOR aimDir;

	//---アニメーション関連---//
	Animation* manAnim;
	int animType;

	bool addRemarks;
};

