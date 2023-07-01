#pragma once
#include<unordered_map>

#include"SelectType.h"
#include"../../Object/ObjectBase/ObjectBase.h"

/*SelectButtonクラス*/
class Select :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Select(SelectType type);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Select();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    void Collision();

    /// <summary>
    /// 入力処理
    /// </summary>
    void Input();

    /// <summary>
    /// 選択フラグ取得
    /// </summary>
    /// <returns>選択された:true|されていない:false</returns>
    bool GetSelect() const { return isSelect; }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

private:
    int mouseX;                      //マウス座標X
    int mouseY;                      //マウス座標Y
    bool canSelect;                  //選択可能状態
    bool isSelect;                   //選択状態
    bool hasInput;                   //入力フラグ

    //描画座標を格納した配列
    std::unordered_map<SelectType, VECTOR> drawPos{
        {SelectType::PLAY,{125,680,0}},
        {SelectType::LOAD,{125,760,0}},
        {SelectType::EXIT,{125,840,0}},
    };

    //画像ハンドルを格納した配列
    std::unordered_map<SelectType, const char*> drawHandle{
        {SelectType::PLAY,"../Assets/BackGround/Play.png"},
        {SelectType::LOAD,"../Assets/BackGround/Load.png"},
        {SelectType::EXIT,"../Assets/BackGround/Exit.png"},
    };

    class Wipe* selectBlend;    //ブレンドモード
};


