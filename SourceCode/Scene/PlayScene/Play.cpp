#include "Play.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/LightingLight/LitLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/MoveGimmic/GhostWalkGim.h"
#include"../../Object/CharaObject/Man/Man.h"
#include "../../UI/Reamarks/Remarks.h"
#include"../EscapeScene/Escape.h"
#include"../Save/Save.h"

    // @brief PlaySceneコンストラクタ //

Play::Play()
    :SceneBase()
{
    //カメラ生成
    ObjManager::Entry(new CameraFps);

    //マップ生成
    ObjManager::Entry(new Map(Map::MapTag::STAGE));

    //家具生成
    ObjManager::Entry(new Furniture(Furniture::FurName::Stage));

    //ドア生成
    ObjManager::Entry(new Door(VGet(22, 0, 0), VGet(0, 180, 0)));
    ObjManager::Entry(new Door(VGet(110, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));

    //イス生成
    ObjManager::Entry(new Chair);

    //照明生成
    ObjManager::Entry(new NomalLight(VGet(-10, 32, 0)));
    ObjManager::Entry(new LitLight(VGet(65, 32, 0), 50.0f));
    ObjManager::Entry(new LitLight(VGet(121, 32, 25), 40.0f));

    //プレイヤー生成
    ObjManager::Entry(new Player);

    //キャラギミック生成
    ObjManager::Entry(new GhostWalkGim);
    ObjManager::Entry(new Man);

    //台詞生成
    ObjManager::Entry(new Remarks(TextType::Stage));
}

// デストラクタ //

Play::~Play()
{
}

// 更新処理 //

SceneBase* Play::Update(float deltaTime)
{
    //オブジェクト更新
    ObjManager::Update(deltaTime);

    //オブジェクト当たり判定
    ObjManager::Collision();

    //キャラクターのギミックが作動し終わったら
    ObjBase* man = ObjManager::GetFirstObj(ObjectTag::Man);
    if (!man)
    {
        //管理クラス内の確保したデータ解放
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();

        //シーンを次の場面にする
        SaveScene::Save(this);
        return new EscapeScene;
    }

    return this;
}

// 描画処理 //

void Play::Draw()
{
    //オブジェクト描画
    ObjManager::Draw();
}