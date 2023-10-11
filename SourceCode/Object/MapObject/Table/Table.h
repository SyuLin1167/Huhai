#pragma once
#include<map>

#include"../../ObjectBase/ObjBase.h"

constexpr int TableNum = 19;

/*Tableクラス*/
class Table :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="objNum">:オブジェクト番号</param>
    Table(const int objNum);

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
};

