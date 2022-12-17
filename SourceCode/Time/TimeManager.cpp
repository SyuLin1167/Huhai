#include "TimeManager.h"

// @brief TimeManagerコンストラクタ― //

TimeManager::TimeManager()
	:nowTime(0)
	, prevTime(0)
	, deltaTime(0)
{}

// @brief Time更新処理 //

void TimeManager::Update()
{
	//---フレームレートの算出---//
	nowTime = (float)GetNowCount();						//現在の時刻を取得
	deltaTime = (nowTime - prevTime) / 1000.0f;		//フレームレートの算出
	prevTime = nowTime;								//過去の時間に現在の時間を代入
}

// @brief TimeManagerデストラクタ― //

TimeManager::~TimeManager()
{
}
