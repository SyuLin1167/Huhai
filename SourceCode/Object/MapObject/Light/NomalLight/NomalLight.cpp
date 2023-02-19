#include "NomalLight.h"

// @brief Lightコンストラクター //

Light::Light()
	:ObjectBase(ObjectTag::Light)
{
	Load();
}

// @brief Lightコンストラクター //

Light::Light(VECTOR LightPos,bool flash)
	:ObjectBase(ObjectTag::Light, LightPos)
{
	Load();
	if (!flash)
	{
		CreatePointLightHandle(LightPos, 70.0f, 0.0f, 0.0f, 0.003f);   
		MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// @brief Lightデストラクター //

Light::~Light()
{
	AssetManager::ReleaseMesh(objHandle);
}

// @brief Light読み込み処理 //

void Light::Load()
{
    //---モデル読み込み---//
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");            //モデル読み込み

    MV1SetPosition(objHandle, objPos);                                                      //モデルの座標設定
    MV1SetScale(objHandle, objScale);                                                       //モデルのサイズ設定
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //モデルの向き設定

    //---当たり判定---//
    colType = CollisionType::Sphere;                                                         //当たり判定は球体

    colSphere.localCenter = VGet(0, -5, 0);                                                 //ローカル座標
    colSphere.Radius = 15.0f;                                                                //球半径
    colSphere.worldCenter = objPos;                                                          //ワールド座標

}

// @brief Light更新処理 //

void Light::Update(float deltaTime)
{

	//---当たり判定設定---//
	ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);         //プレイヤーオブジェクト取得
	if (player)                                                              //オブジェクトの中身が空でなければ
	{
		if (CollisionPair(colSphere, player->GetColSphere()))
		{
		}
	}
	VECTOR distance = player->GetPos()-objPos;
	if (abs(distance.x * distance.x + distance.y + distance.y) < 10)
	{
		CreatePointLightHandle(objPos, 70.0f, 0.0f, 0.0f, 0.01f);
		MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}

	colModel = objHandle;																//当たり判定のモデルはオブジェクトのモデル
	ColUpdate();

}

void Light::Flash(float deltaTime)
{
	srand((unsigned int)time(NULL));
	if (flashTime<=lightTimer)
	{
		lightTimer += deltaTime;
	}
	else
	{

		flashTime = rand() % 2;
		
		lightTimer = 0;
		isFlash = !isFlash;
	}

	//if (isFlash)
	//{
	//	MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	//}
}

// @brief Light描画処理 //

void Light::Draw()
{
	MV1DrawModel(objHandle);						//モデル描画
	DrawFormatString(0, 150, GetColor(255, 255, 255), "%d", isFlash);
	ColDraw();
}