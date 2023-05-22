#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

/*部屋シーンのクラス*/
class Room:public SceneBase
{
public:
	/// <summary>
	/// Roomコンストラクタ
	/// </summary>
	Room();

	/// <summary>
	/// Roomデストラクタ
	/// </summary>
	~Room();

	/// <summary>
	/// Room更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	/// <returns>現在のシーンのポインタ</returns>
	SceneBase* Update(float deltaTime)override;

	/// <summary>
	/// Room描画処理
	/// </summary>
	void Draw()override;

private:
	class BlendMode* roomBlend;
};

