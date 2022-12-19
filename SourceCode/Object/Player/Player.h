#pragma once
#include<DxLib.h>

#include"../ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../ObjectBase/ObjectBase.h"
#include"../../Asset/Animation/Animation.h"
#include"../../Collision/Collision.h"

class Animation;

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
	/// 当たり判定球取得
	/// </summary>
	/// <returns>当たり判定球</returns>
	Sphere GetColSphere() { return colSphere; }

	/// <summary>
	/// Camera更新処理
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void CameraUpdate(float deltTime);

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
	VECTOR UP;								//前方向
	VECTOR DOWN;							//後方向
	VECTOR RIGHT;							//右方向
	VECTOR LEFT;							//左方向

	VECTOR InputVec;						//合成ベクトル
	bool KeyInput;							//キー入力判定

	Sphere colSphere;						//当たり判定球

	//---アニメーション関連---//
	Animation* plyAnim;						//アニメーション
	Anim animType;							//アニメーション状態

	//---カメラ関連---//
	VECTOR cameraPos;						//カメラ位置
	VECTOR cameraFront;						//カメラ正面方向
	const float cameraRotSpeed;				//カメラ回転速度
	const float cameraRad;					//カメラ回転半径
	float cameraYaw;						//水平方向回転角
};