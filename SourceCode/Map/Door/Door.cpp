#include "Door.h"

// @brief Doorコンストラクター //

Door::Door()
    :ObjectBase(ObjectTag::Door)
    ,doorAnim(nullptr)
{
    Load();
}

// @brief Doorコンストラクター //

Door::Door(VECTOR doorPos,VECTOR doorAngle)
    :ObjectBase(ObjectTag::Door,doorPos,doorAngle)
    ,doorAnim(nullptr)
{
    Load();
}

// @brief Doorデストラクター //

Door::~Door()
{
    AssetManager::ReleaseMesh(objHandle);
    delete doorAnim;
}

// @brief Door読み込み処理 //

void Door::Load()
{
    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Door/Door.mv1");            //モデル読み込み

    MV1SetPosition(objHandle, objPos);                                                      //モデルの座標設定
    MV1SetScale(objHandle, objScale);                                                       //モデルのサイズ設定
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //モデルの向き設定

    //---インスタンス---//
    doorAnim = new Animation(objHandle);

    //---アニメーション読み込み---//
    doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/Door.mv1");                        //待機:0
    doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/DoorOpen.mv1", 30.0f, false);      //開:1
    doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/DoorClose.mv1", 30.0f, false);     //閉:2

	animType = IDLE;
	doorAnim->StartAnim(animType);

	colType = CollisionType::Sphere;                                                         //当たり判定は球体

	colSphere.localCenter = VGet(0, 5, 0);                                                 //ローカル座標
	colSphere.Radius = 15.0f;                                                                //球半径
	colSphere.worldCenter = objPos;                                                          //ワールド座標

}

// @brief Door更新処理 //

void Door::Update(float deltaTime)
{
	doorAnim->AddAnimTime(deltaTime);	


	//---当たり判定設定---//
	player = ObjManager::GetFirstObj(ObjectTag::Player);         //プレイヤーオブジェクト取得
	if (player)                                                              //オブジェクトの中身が空でなければ
	{
		if (CollisionPair(colSphere, player->GetColSphere()))
		{
			if (CheckHitKey(KEY_INPUT_E))                //Eキー入力
			{
				if (animType != OPEN || animType == IDLE)                                       //アニメーション開くモーションでなければ
				{
					animType = OPEN;                                        //アニメーションは開くモーション
					doorAnim->StartAnim(animType);                               //開くモーションでアニメーション開始
				}
			}
			if (CheckHitKey(KEY_INPUT_Q))                //Qキー入力
			{

				if (animType = OPEN)                                       //アニメーションが開くモーションだったら
				{
					animType = CLOSE;                                        //アニメーションは閉じるモーション
					doorAnim->StartAnim(animType);                               //閉じるモーションでアニメーション開始
				}
			}
		}

	}
	colModel = objHandle;																//当たり判定のモデルはオブジェクトのモデル
	ColUpdate();
	
}

// @brief Door描画処理 //

void Door::Draw()
{
	MV1DrawModel(objHandle);						//モデル描画
	ColDraw();
}