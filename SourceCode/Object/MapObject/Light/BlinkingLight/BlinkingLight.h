#pragma once
#include<random>
#include<time.h>

#include"../LightBase/LightBase.h"

/*BlinkingLighitのクラス*/
class BlinkingLight :public LightBase
{
public:
	/// <summary>
	/// BlinkingLightコンストラクタ
	/// </summary>
	BlinkingLight();

	/// <summary>
	/// BlinkingLightコンストラクタ
	/// </summary>
	/// <param name="lightPos">:ライトのワールド座標</param>
	BlinkingLight(VECTOR lightPos);

	/// <summary>
	/// BlinkingLightデストラクタ
	/// </summary>
	~BlinkingLight();

	/// <summary>
	/// BlinkingLight読み込み処理
	/// </summary>
	void Load();

	/// <summary>
	/// BlinkingLight更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// BlinkingLight描画処理
	/// </summary>
	void Draw()override;

private:
	float intervalTime;
	float countTimer;
	bool lightBlinking;
};

