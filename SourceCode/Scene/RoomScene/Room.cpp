#include "Room.h"

#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../Object/MapObject/Bed/Bed.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../PlayScene/Play.h"
#include"../Save/Save.h"

// コンストラクタ //

Room::Room()
    :SceneBase()
    , roomBlend(nullptr)
{
    //カメラ生成
    ObjManager::Entry(new CameraFps);

    //マップ生成
    ObjManager::Entry(new Map(Map::MapTag::ROOM));

    //家具生成
    ObjManager::Entry(new Furniture(Furniture::FurName::Room));

    //ベッド生成
    ObjManager::Entry(new Bed);

    //照明生成
    ObjManager::Entry(new NomalLight(VGet(40, 32, 0)));

    //プレイヤー生成
    ObjManager::Entry(new Player);

    //台詞生成
    ObjManager::Entry(new Remarks(TextType::Opening));

    //ブレンドモード生成
    roomBlend = new BlendMode;
}

// デストラクタ //

Room::~Room()
{
}

// 更新処理 //

SceneBase* Room::Update(float deltaTime)
{
    //オブジェクト更新
    ObjManager::Update(deltaTime);

    //オブジェクト当たり判定
    ObjManager::Collision();

    //アクションボタンが押されたら
    ObjBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (!action->IsVisible())
    {
        //フェードアウト
        roomBlend->AddFade(deltaTime);

        //シーン移行時の演出が終わったら
        if (!roomBlend->NowFade())
        {
            //管理クラス内の確保したデータ解放
            AssetManager::ReleaseAllAsset();
            ObjManager::ReleaseAllObj();

            //シーンを次の場面にする
            SaveScene::Save(this);
            return new Play;
        }
    }
    return this;
}

// 描画処理 //

void Room::Draw()
{
    //オブジェクト描画
    ObjManager::Draw();

    //フェード処理
    roomBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    roomBlend->NoBlend();
}