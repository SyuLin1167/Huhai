#include "Room.h"

#include"../PlayScene/Play.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/MapObject/Map/Map.h"
#include"../../Object/MapObject/Bed/Bed.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include"../../UI/Reamarks/Remarks.h"

    // @brief Roomコンストラクタ //

Room::Room()
    :SceneBase()
    , roomBlend(nullptr)
{
    //---カメラ生成---//
    ObjManager::Entry(new CameraFps);

    //---マップ生成---//
    ObjManager::Entry(new Map(Map::MapName::ROOM));

    //---家具を生成---//
    ObjManager::Entry(new Furniture(Furniture::FurName::Room));

    //---ベッドを生成---//
    ObjManager::Entry(new Bed);

    //---プレイヤー生成---//
    ObjManager::Entry(new Player);

    //---照明を生成---//
    ObjManager::Entry(new NomalLight(VGet(40, 32, 0)));

    ObjManager::Entry(new Remarks(TextType::OpeningText));

    roomBlend = new BlendMode;
}

    // @brief Roomデストラクタ //

Room::~Room()
{

}

    // @brief Room更新処理 //

SceneBase* Room::Update(float deltaTime)
{
    ObjManager::Update(deltaTime);
    ObjManager::Collision();

    ObjectBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (!action->IsVisible())                               //Ｒキーが押されたら
    {
        roomBlend->AddFade();
        if (!roomBlend->NowFade())
        {
            AssetManager::ReleaseAllAsset();            //全てのアセットの開放
            ObjManager::ReleaseAllObj();                //全てのオブジェクトの開放
            return new Play;                        //リザルト画面へ
        }
    }
    return this;
}

    // @brief Room描画処理 //

void Room::Draw()
{
    ObjManager::Draw();
    roomBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    roomBlend->NoBlend();
}