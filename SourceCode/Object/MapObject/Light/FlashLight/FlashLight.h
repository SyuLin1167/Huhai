#pragma once
#include<random>
#include<time.h>

#include"../LightBase/LightBase.h"

/*FlashLighitのクラス*/
class FlashLight:public LightBase
{
public:
	/// <summary>
	/// FlashLightコンストラクタ
	/// </summary>
	FlashLight();

	/// <summary>
	/// FlashLightコンストラクタ
	/// </summary>
	/// <param name="lightPos">:ライトのワールド座標</param>
	FlashLight(VECTOR lightPos);

	/// <summary>
	/// FlashLightデストラクタ
	/// </summary>
	~FlashLight();

	/// <summary>
	/// FlashLight読み込み処理
	/// </summary>
	void Load();

	/// <summary>
	/// FlashLight更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// FlashLight描画処理
	/// </summary>
	void Draw()override;

private:
	float intervalTime;
	float countTimer;
	bool lightFlash;
};

