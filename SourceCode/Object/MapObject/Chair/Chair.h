#pragma once
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Collision/Collision.h"

/*Chairのクラス*/
class Chair:public ObjectBase
{
public:
	/// <summary>
	/// Chairコンストラクター
	/// </summary>
	Chair();

	/// <summary>
	/// Chairデストラクター
	/// </summary>
	~Chair();

	/// <summary>
	/// Chair読み込み処理
	/// </summary>
	void Load();

	/// <summary>
	/// Chair更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime)override;

	/// <summary>
	/// Chair描画処理
	/// </summary>
	void Draw()override;

	enum Anim
	{
		IDLE = 0,			//待機
		MOVE,
	};
private:
	//---アニメーション関連---//
	class Animation* ChairAnim;			//アニメーション
	int animType;						//アニメーション状態
};

