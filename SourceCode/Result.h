#pragma once
#include<DxLib.h>
#include"SceneBase/SceneBase.h"

/*リザルトシーンのクラス*/
class Result :public SceneBase
{
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	Result();

	/// <summary>
	/// デストラクター
	/// </summary>
	~Result();

	/// <summary>
	/// ResultScene更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <returns>現在のシーンのポインタ</returns>
	SceneBase* Update(float deltaTime)override;

	/// <summary>
	/// リザルトシーンの描画
	/// </summary>
	void Draw()override;

};
