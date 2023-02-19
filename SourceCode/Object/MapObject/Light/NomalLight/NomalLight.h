#pragma once
#include<DxLib.h>
#include<time.h>

#include"../../../../Asset/AssetManager/AssetManager.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Collision/Collision.h"

/*Lightのクラス*/
class Light :public ObjectBase
{
public:
	/// <summary>
	/// Lightコンストラクター
	/// </summary>
	Light();

	/// <summary>
	/// Lightコンストラクター
	/// </summary>
	/// <param name="LightPos">:イスのワールド座標</param>
	Light(VECTOR LightPos,bool flash=false);


	/// <summary>
	/// Lightデストラクター
	/// </summary>
	~Light();

	/// <summary>
	/// Light読み込み処理
	/// </summary>
	void Load();

	/// <summary>
	/// Light更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime)override;

	void Flash(float deltaTime);

	/// <summary>
	/// Light描画処理
	/// </summary>
	void Draw()override;

private:
	float lightBright;
	bool isFlash;
	int flashTime;
	int lightTimer;
};
