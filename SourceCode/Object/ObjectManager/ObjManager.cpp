#include "ObjManager.h"

ObjManager* ObjManager::objInstance = nullptr;				//ObjManager実体へのポインタ定義

// @brief ObjManagerコンストラクター //

ObjManager::ObjManager()
	:Object()
{
	objInstance = nullptr;
}

// @brief ObjManagerデストラクター //

ObjManager::~ObjManager()
{
	ReleaceAllObj();										//すべてのオブジェクトを削除
}

// @brief ObjManager初期化処理 //

void ObjManager::Init()
{
	if (!objInstance)										//ポインタが空だったら
	{
		objInstance = new ObjManager;						//ポインタ初期化
	}
}

// @brief オブジェクト登録 //

void ObjManager::Entry(ObjectBase* newObj)
{
	objInstance->holdObj.emplace_back(newObj);				//オブジェクト一時保存
}

//@brief オブジェクト削除 //

void ObjManager::Release(ObjectBase* releaseObj)
{
	auto iter = find(objInstance->holdObj.begin(),
		objInstance->holdObj.end(), releaseObj);			//一時保存オブジェクト内を検索

	if (iter != objInstance->holdObj.end())					//オブジェクトが見つかったら
	{
		iter_swap(iter, objInstance->holdObj.end() - 1);	//見つけたオブジェクトを最後尾に移動
		objInstance->holdObj.pop_back();					//データを削除
		return;
	}

	iter = find(objInstance->Object.begin(),
		objInstance->Object.end(), releaseObj);				//アクティブオブジェクト内を検索

	if (iter != objInstance->Object.end())					//オブジェクトが見つかったら
	{
		iter_swap(iter, objInstance->Object.end() - 1);		//見つけたオブジェクトを末尾に移動
		delete objInstance->Object.back();					//オブジェクト削除
	}
}

// @brief 全オブジェクト削除 //

void ObjManager::ReleaceAllObj()
{
	while (!objInstance->holdObj.empty())					//一時保存オブジェクト内が空になるまで
	{
		delete objInstance->holdObj.back();					//末尾からデータ削除
		objInstance->holdObj.pop_back();					//末尾から要素削除
	}

	while (!objInstance->Object.empty())					//アクティブオブジェクト内が空になるまで
	{
		delete objInstance->Object.back();					//末尾からデータ削除
		objInstance->Object.pop_back();						//末尾から要素削除
	}
}

// @brief 全オブジェクトの更新処理 //

void ObjManager::Update(float deltaTime)
{
	for (auto obj : objInstance->Object)			//すべてのアクターの更新
	{
		obj->Update(deltaTime);								//該当タグにあるすべてのオブジェクトを更新
	}

	for (auto holding : objInstance->holdObj)		//一時保存中のオブジェクトをアクティブリストに追加
	{
		objInstance->Object.emplace_back(holding);		//保存中のオブジェクトデータをオブジェクトへ移動
	}
	objInstance->holdObj.clear();							//全て移し終わったら一時保存オブジェクト内を空にする

	Dead();
}

// @brief オブジェクトの生死状況 //

void ObjManager::Dead()
{
	vector<ObjectBase*>deadObj;										//死亡オブジェクト
	for (int i = 0; i < objInstance->Object.size(); i++)			//死亡しているオブジェクトを検索
	{
		if (!objInstance->Object[i]->IsAlive())						//オブジェクトが生きていなかったら
		{
			deadObj.emplace_back(objInstance->Object[i]);		//死亡オブジェクトへ移動

			objInstance->Object.erase(
				remove_if(objInstance->Object.begin(), objInstance->Object.end(),
					[](ObjectBase* gObj) {return !gObj->IsAlive(); }), objInstance->Object.cend());
		}
	}

	while (!deadObj.empty())										//死亡オブジェクトが空になるまで
	{
		delete deadObj.back();										//末尾から削除
		deadObj.pop_back();											//末尾のデータを削除
	}

}

// @brief オブジェクトの描画処理 //

void ObjManager::Draw()
{
	for (auto obj : objInstance->Object)			//全てのアクターの描画
	{
		obj->Draw();										//該当タグにある全てのオブジェクトを描画
	}
}

// @birief ObjManagerの開放 //

void ObjManager::Finalize()
{
	ReleaceAllObj();										//全てのオブジェクト開放
	if (objInstance)										//objManagerに実態があったら
	{
		delete objInstance;									//削除
	}
}