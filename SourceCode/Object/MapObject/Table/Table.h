#pragma once

#include<map>

#include"../../ObjectBase/ObjectBase.h"

constexpr int TableNum = 19;

/*Tableクラス*/
class Table :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="objNum">:オブジェクト番号</param>
    Table(int objNum);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Table();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

private:
    //座標データ
    std::map<int, VECTOR> posData
    {
        {0,{215,0,7}},{1,{220,0,-22}},{2,{250,0,-10}},
        {3,{240,0,18}},{4,{285,0,-15}},{5,{320,0,22}},
        {6,{340,0,-8}},{7,{400,0,10}},{8,{440,0,-10}},
        {9,{480,0,10}},{10,{520,0,0}},{11,{520,0,-22}},
        {12,{520,0,22}},{13,{550,0,-11}},{14,{560,0,13}},
        {15,{600,0,17}},{16,{610,0,-11}},{17,{645,0,-17}},
        {18,{640,0,11}},
    };

    //向きデータ
    std::map<int, float> dirData
    {
        {0,0.0f},{1,90.0f},{2,0.0f},
        {3,-75.0f},{4,0.0f},{5,90.0f},
        {6,90.0f},{7,0.0f},{8,0.0f},
        {9,0.0f},{10,90.0f},{11,90.0f},
        {12,90.0f},{13,35.0f},{14,90.0f},
        {15,0.0f},{16,-65.0f},{17,0.0f},
        {18,-65.0f},
    };
};

