#include "ObjManager.h"

#include"../../Shade/Bloom/Bloom.h"
#include"../../Scene/PauseMenu/PauseMenu.h"

//実態へのポインタ定義
ObjManager* ObjManager::objManager = nullptr;

// コンストラクタ //

ObjManager::ObjManager()
    :Object()
    , holdObj()
    , bloom(nullptr)
{
    bloom = new Bloom;
}

// デストラクタ //

ObjManager::~ObjManager()
{
    //インスタンス削除
    if (bloom)
    {
        delete bloom;
    }
}

// 初期化処理 //

void ObjManager::Init()
{
    //インスタンス生成
    if (!objManager)
    {
        objManager = new ObjManager;
    }
}

// 登録 //

void ObjManager::Entry(ObjBase* newObj)
{
    //一時保存場所にオブジェクト追加
    objManager->holdObj.emplace_back(newObj);
}

// 削除 //

void ObjManager::Release(ObjBase* releaseObj)
{
    //保存場所のオブジェクト検索
    auto iter = find(objManager->holdObj.begin(),
        objManager->holdObj.end(), releaseObj);

    //オブジェクトが見つかったら末尾に移して削除
    if (iter != objManager->holdObj.end())
    {
        std::iter_swap(iter, objManager->holdObj.end() - 1);
        objManager->holdObj.pop_back();
        return;
    }

	//アクティブにあるタグのオブジェクト検索
    ObjectTag tag = releaseObj->GetTag();					
    iter = find(objManager->Object[tag].begin(),
        objManager->Object[tag].end(), releaseObj);

    //オブジェクトが見つかったら末尾に移して削除
    if (iter != objManager->Object[tag].end())
    {
        std::iter_swap(iter, objManager->Object[tag].end() - 1);
        delete objManager->Object[tag].back();
    }
}

// 全削除 //

void ObjManager::ReleaseAllObj()
{
    //一時保存場所の中が空になるまで末尾からオブジェクト削除
    while (!objManager->holdObj.empty())
    {
        delete objManager->holdObj.back();
        objManager->holdObj.pop_back();
    }

    //アクティブの中が空になるまで末尾からオブジェクト削除
    for (auto& tag : ObjTagAll)
    {
        while (!objManager->Object[tag].empty())
        {
            delete objManager->Object[tag].back();
            objManager->Object[tag].pop_back();
        }
    }
}

// 全更新処理 //

void ObjManager::Update(float deltaTime)
{

    // 該当タグにあるすべてのオブジェクトを更新
    for (auto& tag : ObjTagAll)
    {
        for (int i = 0; i < objManager->Object[tag].size(); ++i)
        {
            objManager->Object[tag][i]->Update(deltaTime);
        }
    }

    //ブルーム用画面
    if (PauseMenu::HasStatus("Bloom"))
    {
        objManager->bloom->SetColoerScreen();
    }
    else
    {
        SetCameraNearFar(0.1f, 400.0f);
    }

    //一時保存中のオブジェクトをアクティブリストに追加
    for (auto holding : objManager->holdObj)
    {
        ObjectTag tag = holding->GetTag();
        objManager->Object[tag].emplace_back(holding);
    }

    //全て移し終わったら保存場所の中身を空にする
    objManager->holdObj.clear();

    Dead();
}

// 死亡処理 //

void ObjManager::Dead()
{

    //死亡したオブジェクトを検索して死亡オブジェクトに移動
    std::vector<ObjBase*>deadObj;
    for (auto& tag : ObjTagAll)
    {
        for (auto obj : objManager->Object[tag])
        {
            if (!obj->IsAlive())
            {
                deadObj.emplace_back(obj);
            }
        }
        objManager->Object[tag].erase(remove_if(begin(objManager->Object[tag]), end(objManager->Object[tag]),
            [](ObjBase* dead) {return !dead->IsAlive(); }), cend(objManager->Object[tag]));
    }

    //死亡オブジェクトの中身が空になるまで削除
	while (!deadObj.empty())
    {
        delete deadObj.back();
        deadObj.pop_back();
    }
}

// 全描画処理 //

void ObjManager::Draw()
{
    //該当タグにあるすべてのオブジェクトを描画
    for (auto& tag : ObjTagAll)
    {

        for (int i = 0; i < objManager->Object[tag].size(); ++i)
        {
            if (objManager->Object[tag][i]->IsVisible())
            {
                objManager->Object[tag][i]->Draw();
            }
        }
    }

    //ブルーム描画
    if (PauseMenu::HasStatus("Bloom"))
    {
        objManager->bloom->SetBloomGraph();
        objManager->bloom->Draw();
    }
}

// 当たり判定処理 //

void ObjManager::Collision()
{
    //当たり判定の組み合わせ
    //Ghost
    for (int gstNum = 0; gstNum < objManager->Object[ObjectTag::Ghost].size(); ++gstNum)
    {
        for (int mapNum = 0; mapNum < objManager->Object[ObjectTag::Map].size(); ++mapNum)
        {
            objManager->Object[ObjectTag::Ghost][gstNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Map][mapNum]);
        }
        for (int plyNum = 0; plyNum < objManager->Object[ObjectTag::Player].size(); ++plyNum)
        {
            objManager->Object[ObjectTag::Ghost][gstNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Player][plyNum]);
        }
    }

    //Player
    for (int plyNum = 0; plyNum < objManager->Object[ObjectTag::Player].size(); ++plyNum)
    {
        for (int mapNum = 0; mapNum < objManager->Object[ObjectTag::Map].size(); ++mapNum)
        {
            objManager->Object[ObjectTag::Player][plyNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Map][mapNum]);
        }
        for (int furNum = 0; furNum < objManager->Object[ObjectTag::Furniture].size(); ++furNum)
        {
            objManager->Object[ObjectTag::Player][plyNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Furniture][furNum]);
        }
        for (int gstNum = 0; gstNum < objManager->Object[ObjectTag::Ghost].size(); ++gstNum)
        {
            objManager->Object[ObjectTag::Player][plyNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Ghost][gstNum]);
        }
    }
}

// タグの先頭オブジェクト取得 //

ObjBase* ObjManager::GetFirstObj(ObjectTag tag)
{
    //オブジェクトの数が0だったらnullptrを返す
    if (objManager->Object[tag].size() == 0)		
    {
        return nullptr;
    }

    //タグ種の最初のオブジェクトを返す
    return objManager->Object[tag][0];
}

// タグの指定オブジェクト取得 //

ObjBase* ObjManager::GetObj(ObjectTag tag, int tagNum)
{
    //オブジェクトの数が指定数より少なかったらnullptrを返す
    if (objManager->Object[tag].size() < static_cast<unsigned long long>(tagNum) + 1)
    {
        return nullptr;
    }

    //タグ種のtagNum番目のオブジェクトを返す
    return objManager->Object[tag][tagNum];
}

// 後処理 //

void ObjManager::Finalize()
{
    //全オブジェクト解放
    ReleaseAllObj();

    //インスタンス削除
    if (objManager)
    {
        delete objManager;
    }
}