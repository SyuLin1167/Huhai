#include "BlinkingLight.h"

// @brief BlinkingLightコンストラクタ //

BlinkingLight::BlinkingLight()
	:LightBase()
	, intervalTime(0.0f)
	, countTimer(0.0f)
	, lightBlinking(false)
{
	Load();
}

// @brief BlinkingLightコンストラクタ //

BlinkingLight::BlinkingLight(VECTOR lightPos)
	:LightBase(lightPos)
{
	Load();
}

// @brief BlinkingLightデストラクタ //

BlinkingLight::~BlinkingLight()
{
	DeleteLightHandle(lightHandle);
	AssetManager::ReleaseMesh(objHandle);
}

// @brief BlinkingLight読み込み処理 //

void BlinkingLight::Load()
{
	lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
	MV1SetPosition(objHandle, objPos);
	MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

// @brief BlinkingLight更新処理 //

void BlinkingLight::Update(float deltaTime)
{

	SetLightRangeAttenHandle(lightHandle, lightRange, 0.0f, 0.0f, lightAtten2);

	if (countTimer >= intervalTime)
	{
		countTimer = 0;
		srand((unsigned int)time(NULL));
		intervalTime = static_cast <float>(rand() % 4 + 1);
	}

	if (intervalTime <= 1)
	{
		lightBlinking = !lightBlinking;
	}
	else
	{
		lightBlinking = false;
	}

	if (lightBlinking)
	{
		lightAtten2 = 0.003f;
	}
	else
	{
		lightAtten2 = 0.002f;
	}

	countTimer += deltaTime;
}

// @brief BlinkingLight描画処理 //

void BlinkingLight::Draw()
{
	MV1DrawModel(objHandle);						//モデル描画
}