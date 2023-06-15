#pragma once
#include<DxLib.h>
#include"../SceneBase/SceneBase.h"

	/*ResultSceneクラス*/
class Result :public SceneBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Result();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Result();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <returns>現在のシーンのポインタ</returns>
	SceneBase* Update(float deltaTime)override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;

};
