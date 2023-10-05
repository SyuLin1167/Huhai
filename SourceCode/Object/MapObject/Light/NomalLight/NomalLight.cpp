#include "NomalLight.h"

// コンストラクタ //

NomalLight::NomalLight(std::string scene, std::string num)
    :LightBase(scene,num)
{
}
// デストラクタ //

NomalLight::~NomalLight()
{
    //処理なし
}


// 更新処理 //

void NomalLight::Update(float deltaTime)
{
    //パラメーターによる距離減衰
    AttenByParam();
}

// 描画処理 //

void NomalLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}