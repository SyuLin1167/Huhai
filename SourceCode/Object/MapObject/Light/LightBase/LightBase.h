#pragma once
#include<unordered_map>

#include"../../../ObjectBase/ObjBase.h"
#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"

/// <summary>
/// LightBaseクラス
/// </summary>
class LightBase :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    LightBase();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="scene">:シーン名</param>
    /// <param name="num">:オブジェクト番号</param>
    LightBase(std::string scene, std::string num);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~LightBase();

    /// <summary>
    /// パラメータによる距離減衰
    /// </summary>
    void AttenByParam();

protected:
    const float DECIMAL_CONV = 10000.0f;    //十進数変換用

    int lightHandle;                        //ライトハンドル
    const float LIGHT_POS_Y = 35.5f;        //ライトの高さ
    const float LIGHTMODEL_POS_Y = 33.0f;   //モデルの高さ

    const float LIGHT_RANGE = 70.0f;        //距離減衰有効距離
    const float MIN_ATTEN_PARAM=0.01f;      //減衰最小値
    float lightAtten2;                      //距離減衰係数

    const COLOR_F LIGHT_MAT_COLOR;            //ライトのマテリアルカラー

};
