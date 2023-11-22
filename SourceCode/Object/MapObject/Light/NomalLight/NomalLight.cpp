#include "NomalLight.h"

NomalLight::NomalLight(std::string scene, std::string num)
    :LightBase(scene,num)
{
    //処理なし
}

NomalLight::~NomalLight()
{
    //処理なし
}


void NomalLight::Update(float deltaTime)
{
    //パラメーターによる距離減衰
    AttenByParam();
}

void NomalLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}