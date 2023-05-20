#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

/*Day1部屋シーンのクラス*/
class Day1Room:public SceneBase
{
public:
	/// <summary>
	/// Day1Roomコンストラクタ
	/// </summary>
	Day1Room();

	/// <summary>
	/// Day1Roomデストラクタ
	/// </summary>
	~Day1Room();

	/// <summary>
	/// Day1Room更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	/// <returns>現在のシーンのポインタ</returns>
	SceneBase* Update(float deltaTime)override;

	/// <summary>
	/// Day1Room描画処理
	/// </summary>
	void Draw()override;

private:
	class Remarks* remarks;
	class Action* action;
	class BlendMode* roomBlend;
};

