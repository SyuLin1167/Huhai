#pragma once
#include<DxLib.h>

#include"../ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../ObjectBase/ObjectBase.h"
#include"../../Asset/Animation/Animation.h"
#include"../../Collision/Collision.h"

/* Playerのクラス */
class Player :public ObjectBase
{
public:
	/// <summary>
	/// Playerコンストラクター
	/// </summary>
	Player();

	/// <summary>
	/// Playerデストラクター
	/// </summary>
	~Player();

	/// <summary>
	/// Player更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Update(float deltaTime) override;

	/// <summary>
	/// Player描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// Player衝突時処理
	/// </summary>
	/// <param name="other">:オブジェクト</param>
	void OnCollisionEnter(const ObjectBase* other)override;

	/// <summary>
	/// アニメーションステータス
	/// </summary>
	typedef enum Anim
	{
		IDLE = 0,							//待機
		RUN,								//走り
		ATACK								//攻撃
	};

private:
	/// <summary>
	/// Player移動処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void Move(float deltaTime);

	/// <summary>
	/// Player回転処理
	/// </summary>
	void Rotate();

	//---アニメーション関連---//
	class Animation* plyAnim;				//アニメーション
	int animType;							//アニメーション状態

	VECTOR UP;								//前方向
	VECTOR DOWN;							//後方向
	VECTOR RIGHT;							//右方向
	VECTOR LEFT;							//左方向

	VECTOR inputVec;						//合成ベクトル
	VECTOR inputVel;						//速度ベクトル
	VECTOR aimDir;							//目標方向
	bool inputKey;							//キー入力判定
	bool nowRoted;							//現在回転中かどうか

	//---当たり判定関連---//
	class Collision* plyCol;				//コリジョン
	Collision::Sphere colSphere;			//当たり判定球

	//---カメラ関連---//
	VECTOR camFront;						//カメラ前方向
};