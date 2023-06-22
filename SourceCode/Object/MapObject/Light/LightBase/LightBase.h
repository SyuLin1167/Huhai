#pragma once
#include<unordered_map>

#include"LightPosTag.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"

/*Light基底クラス*/
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
    /// <param name="pos">ワールド座標</param>
    LightBase(VECTOR pos);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~LightBase();

    /// <summary>
    /// 読み込み処理
    /// </summary>
    void Load();

protected:
    int lightHandle;            //ライトハンドル

    float lightRange;			//距離減衰有効距離
    float lightAtten2;			//距離減衰係数

    COLOR_F lightMatColor;		//ライトのマテリアルカラー

};
