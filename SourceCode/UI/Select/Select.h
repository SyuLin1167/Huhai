#pragma once
#include<unordered_map>

#include"SelectType.h"
#include"../../Object/ObjectBase/ObjectBase.h"
#include"../../BlendMode/BlendMode.h"

using namespace std;

/*セレクトボタンクラス*/
class Select:public ObjectBase
{
    class BlendMode* selectBlend;

public:
    /// <summary>
    /// Selectコンストラクタ
    /// </summary>
    Select(SelectType type);

    /// <summary>
    /// Selectデストラクタ
    /// </summary>
    ~Select();

    /// <summary>
    /// Select更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Select当たり判定処理
    /// </summary>
    void OnCollisionEnter();

    /// <summary>
    /// 選択フラグ取得
    /// </summary>
    /// <returns>選択されたかどうか</returns>
    bool GetSelect() { return isSelect; }

    /// <summary>
    /// Select描画処理
    /// </summary>
    void Draw()override;

private:
    int mouseX;                     //マウス座標X
    int mouseY;                     //マウス座標Y
    bool isSelect;                  //選択されたかどうか
    bool nowInput;                  //入力中かどうか

    //描画座標を格納した配列
    unordered_map<SelectType, VECTOR> drawPos{
        {SelectType::PLAY,{125,680,0}},
        {SelectType::LOAD,{125,760,0}},
        {SelectType::EXIT,{125,840,0}},
    };

    //画像ハンドルを格納した配列
    unordered_map<SelectType, const char*> drawHandle{
        {SelectType::PLAY,"../Assets/BackGround/Play.png"},
        {SelectType::LOAD,"../Assets/BackGround/Load.png"},
        {SelectType::EXIT,"../Assets/BackGround/Exit.png"},
    };
};


