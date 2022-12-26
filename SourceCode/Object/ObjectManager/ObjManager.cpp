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

	ObjectTag tag = releaseObj->GetTag();					//解放オブジェクトのタグ種類取得

	iter = find(objInstance->Object[tag].begin(),
		objInstance->Object[tag].end(), releaseObj);				//アクティブオブジェクト内を検索

	if (iter != objInstance->Object[tag].end())					//オブジェクトが見つかったら
	{
		iter_swap(iter, objInstance->Object[tag].end() - 1);		//見つけたオブジェクトを末尾に移動
		delete objInstance->Object[tag].back();					//オブジェクト削除
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

	for (auto& tag : ObjTagAll)					//アクティブオブジェクト内が空になるまで
	{
		while (!objInstance->Object[tag].empty())				//空でなければ
		{
			delete objInstance->Object[tag].back();					//末尾からデータ削除
			objInstance->Object[tag].pop_back();						//末尾から要素削除
		}
	}
}

// @brief 全オブジェクトの更新処理 //

void ObjManager::Update(float deltaTime)
{
	for (auto& tag : ObjTagAll)
	{
		// 該当タグにあるすべてのオブジェクトを更新
		for (int i = 0; i < objInstance->Object[tag].size(); ++i)
		{
			objInstance->Object[tag][i]->Update(deltaTime);
		}
		//for (auto obj : objInstance->Object[tag])			//すべてのアクターの更新
		//{
		//	obj->Update(deltaTime);								//該当タグにあるすべてのオブジェクトを更新
		//}
	}
	for (auto holding : objInstance->holdObj)		//一時保存中のオブジェクトをアクティブリストに追加
	{
		ObjectTag tag = holding->GetTag();					//解放オブジェクトのタグ種類取得
		objInstance->Object[tag].emplace_back(holding);		//保存中のオブジェクトデータをオブジェクトへ移動
	}
	objInstance->holdObj.clear();							//全て移し終わったら一時保存オブジェクト内を空にする

	Dead();
}

// @brief オブジェクトの生死状況 //

void ObjManager::Dead()
{
	vector<ObjectBase*>deadObj;										//死亡オブジェクト
	for (auto& tag : ObjTagAll)
	{
		for (auto alive: objInstance->Object[tag])			//死亡しているオブジェクトを検索
		{
			// タグ内をすべて回り、死亡Objectを検索し、deadObjectsへ
			for (int i = 0; i < objInstance->Object[tag].size(); ++i)
			{
				if (!objInstance->Object[tag][i]->IsAlive())
				{
					deadObj.emplace_back(objInstance->Object[tag][i]);
				}
			}
			//if (alive->IsAlive())						//オブジェクトが生きていなかったら
			//{
			//	deadObj.emplace_back(objInstance->Object[tag]);		//死亡オブジェクトへ移動

			//	objInstance->Object[tag].erase(
			//		remove_if(objInstance->Object[tag].begin(), objInstance->Object[tag].end(),
			//			[](ObjectBase* gObj) {return !gObj->IsAlive(); }), objInstance->Object[tag].cend());
			//}
		}
	}

	for (auto dead : deadObj)							//死亡オブジェクトを削除
	{
		delete dead;											//削除
	}
	deadObj.clear();											//全て削除し終わったら死亡オブジェクト内を空にする
}

// @brief オブジェクトの描画処理 //

void ObjManager::Draw()
{
	for (auto& tag : ObjTagAll)
	{
		for (int i = 0; i < objInstance->Object[tag].size(); ++i)
		{
			// 描画可能なオブジェクトのみ描画
			if (objInstance->Object[tag][i]->IsVisible())
			{
				objInstance->Object[tag][i]->Draw();
			}
		}
		//for (auto obj : objInstance->Object[tag])			//全てのアクターの描画
		//{
		//	obj->Draw();										//該当タグにある全てのオブジェクトを描画
		//}
	}
}

// @brief タグ種の最初のオブジェクト取得 //

ObjectBase* ObjManager::GetFirstObj(ObjectTag tag)
{
	if (objInstance->Object[tag].size() == 0)		//オブジェクトの数が0だったら
	{
		return nullptr;								//空なのでnullptrを返す
	}
	return objInstance->Object[tag][0];				//タグ種の最初のオブジェクトを返す
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