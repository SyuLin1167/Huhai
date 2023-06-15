#pragma once
#include"../../Object/ObjectBase/ObjectBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

constexpr float actionRange = 30.0f;

        /*アクションボタンクラス*/
class Action :public ObjectBase
{
    class BlendMode* actionBlend;
public:
    /// <summary>
    /// Actionコンストラクタ
    /// </summary>
    /// <param name="objpos">:描画座標</param>
    Action(VECTOR objpos);

    /// <summary>
    /// Actionデストラクタ
    /// </summary>
    ~Action();

    /// <summary>
    /// Action更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Action描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// アクション中かどうか
    /// </summary>
    /// <returns>アクション中かどうか</returns>
    bool IsAction() { return isAction; }

private:
    float objDistance;      //オブジェクトとの距離
    bool canAction;         //アクション可能かどうか
    bool isAction;          //アクション中かどうか
};
