#pragma once
#include<unordered_map>

#include"LightPosTag.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"

        /*Lightの基底クラス*/
class LightBase :public ObjectBase
{
public:
    /// <summary>
    /// LightBaseコンストラクタ
    /// </summary>
    LightBase();

    /// <summary>
    /// LightBaseコンストラクタ
    /// </summary>
    /// <param name="lightPos">ライトのワールド座標</param>
    LightBase(VECTOR lightPos);

    /// <summary>
    /// LightBaseのデストラクタ
    /// </summary>
    ~LightBase();

    /// <summary>
    /// LightBase読み込み処理
    /// </summary>
    void Load();

protected:
    int lightHandle;

    float lightRange;			//距離減衰有効距離
    float lightAtten2;			//距離減衰係数

    COLOR_F lightMatColor;		//ライトのマテリアルカラー

};
