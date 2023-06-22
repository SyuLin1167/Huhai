#pragma once
#include"../../Object/ObjectBase/ObjectBase.h"


/*ActionButtonクラス*/
class Action :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">:描画座標</param>
    Action(VECTOR pos);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Action();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// リアクション
    /// </summary>
    /// <returns>反応中:true|無反応:false</returns>
    bool IsAction() const { return isAction; }

private:
    const float actionRange = 30.0f;    //範囲
    float toDistance;                   //距離

    bool canAction;                     //反応可能状態
    bool isAction;                      //反応状態

    class BlendMode* actionBlend;       //ブレンドモード
};
