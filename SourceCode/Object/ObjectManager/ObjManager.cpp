#include<assert.h>

#include"../../Shade/Bloom/Bloom.h"
#include "ObjManager.h"

std::unique_ptr<ObjManager> ObjManager::singleton = nullptr;

ObjManager::ObjManager()
    :object()
    , bloom(new Bloom)
{
    //処理なし
}

ObjManager::~ObjManager()
{
    DeleteAllObj();
}

void ObjManager::Init()
{
    //インスタンス生成
    if (!singleton)
    {
        singleton.reset(new ObjManager);
    }
}

void ObjManager::AddObj(ObjBase* newObj)
{
    ObjTag tag = newObj->GetTag();
    singleton->object[tag].emplace_back(newObj);
}

void ObjManager::UpdateAllObj(const float deltaTime)
{
    //全タグ分更新処理をまとめて行う
    for (auto& tag : ObjTagAll)
    {
        for (auto& obj : singleton->object[tag])
        {
            obj->Update(deltaTime);
        }
    }

    //ブルーム用画面
    singleton->bloom->SetColoerScreen();

    singleton->OnDeadObj();
}

void ObjManager::DrawAllObj()
{
    //全タグ分描画処理をまとめて行う
    for (auto& tag : ObjTagAll)
    {
        for (auto& obj : singleton->object[tag])
        {
            //オブジェクトが可視なら描画させる
            if (obj->IsVisible())
            {
                obj->Draw();
            }
        }
    }

    //ブルーム描画
    singleton->bloom->SetBloomGraph();
    singleton->bloom->Draw();
}

void ObjManager::OnDeadObj()
{
    //全タグ分死亡オブジェクトを探して削除
    for (auto& tag : ObjTagAll)
    {
        for (auto& dead : singleton->object[tag])
        {
            //死んでいたらオブジェクト削除
            if (!dead->IsAlive())
            {
                singleton->DeleteObj(dead);
            }
        }
    }
}

void ObjManager::DeleteObj(std::shared_ptr<ObjBase>& deleteObj)
{
    //削除オブジェクトのタグ取得
    ObjTag tag = deleteObj->GetTag();

    //オブジェクトを検索
    auto endObj = singleton->object[tag].end();
    auto findObj = std::find(singleton->object[tag].begin(), endObj, deleteObj);

    //見つかったら末尾に移動させて削除
    if (findObj != endObj)
    {
        std::swap(findObj, endObj);
        singleton->object[tag].pop_back();
    }
}

void ObjManager::DeleteAllObj()
{
    //空じゃなかったらオブジェクト削除
    for (auto& tag : ObjTagAll)
    {
        if (!singleton->object[tag].empty())
        {
            singleton->object[tag].clear();
        }
    }
}

void ObjManager::OnCollision()
{
    //当たり判定の組み合わせ
    //Ghost
    for (auto& gstCol: singleton->object[ObjTag::Ghost])
    {
        for (auto& mapCol :singleton->object[ObjTag::Map])
        {
            gstCol->OnCollisionEnter(mapCol.get());
        }
        for (auto& plyCol:singleton->object[ObjTag::Player])
        {
            gstCol->OnCollisionEnter(plyCol.get());
        }
    }

    //Player
    for (auto& plyCol :singleton->object[ObjTag::Player])
    {
        for (auto& mapCol:singleton->object[ObjTag::Map])
        {
            plyCol->OnCollisionEnter(mapCol.get());
        }
        for (auto& furCol : singleton->object[ObjTag::Furniture])
        {
            plyCol->OnCollisionEnter(furCol.get());
        }
        for (auto& gstCol : singleton->object[ObjTag::Ghost])
        {
            plyCol->OnCollisionEnter(gstCol.get());
        }
    }
}

ObjBase* ObjManager::GetFirstObj(ObjTag tag)
{
    //オブジェクトの数が0だったらnullptrを返す
    if (singleton->object[tag].size() == 0)
    {
        return nullptr;
    }

    //タグ種の最初のオブジェクトを返す
    return singleton->object[tag][0].get();
}

ObjBase* ObjManager::GetObj(ObjTag tag, int tagNum)
{
    //オブジェクトの数が指定数より少なかったらnullptrを返す
    if (singleton->object[tag].size() < static_cast<unsigned long long>(tagNum) + 1)
    {
        return nullptr;
    }

    //タグ種のtagNum番目のオブジェクトを返す
    return singleton->object[tag][tagNum].get();
}