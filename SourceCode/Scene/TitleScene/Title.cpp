#include "Title.h"

#include "../../Object/ObjectManager/ObjManager.h"
#include "../../Asset/AssetManager/AssetManager.h"
#include "../../BlendMode/BlendMode.h"
#include "../../Asset/Sound/Sound.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include "../RoomScene/Room.h"
#include "../Save/Save.h"

// コンストラクタ //

TitleScene::TitleScene()
    :SceneBase()
{
    //タイトルロゴ生成
    BgHandle = AssetManager::GetGraph("../Assets/BackGround/Title.png");
    BgX = 180;
    BgY = 150;

    //ブレンドモード生成
    titleBlend = new Blend;

    //サウンド生成
    titleSound = new Sound;
    titleSound->AddSound("../Assets/Sound/TitleBgm.mp3", SoundTag::Title);
    titleSound->AddSound("../Assets/Sound/StartSE.mp3", SoundTag::Start);
    titleSound->StartSound(SoundTag::Title, DX_PLAYTYPE_LOOP);

    //カメラ生成
    ObjManager::Entry(new FixedCamera);

    //マップ生成
    ObjManager::Entry(new Map(Map::MapTag::TITLE));

    //ドア生成
    door = new Door(VGet(0, 0, 66), VGet(-1, 0, 0));
    ObjManager::Entry(door);

    //ライト生成
    ObjManager::Entry(new BlinkingLight(VGet(-35, 33, 70)));
    ObjManager::Entry(new NomalLight(VGet(65, 33, 65)));

    //選択ボタン生成
    for (auto type : selectTypeAll)
    {
        select[type] = new Select(type);
    }

    //グラフ作成
    screenGraph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// デストラクタ //

TitleScene::~TitleScene()
{
    //画像ハンドル削除
    if (BgHandle)
    {
        DeleteGraph(BgHandle);
    }
}

// 更新処理 //

SceneBase* TitleScene::Update(float deltaTime)
{
    //マウスポインター表示
    SetMouseDispFlag(TRUE);

    //ドアは開く状態にする
    door->MoveAnim(Door::Anim::OPEN);

    //オブジェクト更新
    ObjManager::Update(deltaTime);
    for (auto type : selectTypeAll)
    {
        select[type]->Update(deltaTime);

        //ボタン選択時処理
        if (select[type]->GetButtonInput())
        {
            //マウス座標を画面の中心にして非表示にする
            SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            SetMouseDispFlag(false);

            //フェードアウト
            titleBlend->AddFade(deltaTime);

            //EXIT選択時、シーンをnullptrにする
            if (type == EXIT)
            {
                return nullptr;
            }
            else
            {
                //EXIT以外選択時、SEを再生
                titleSound->StartSoundOnce(SoundTag::Start, DX_PLAYTYPE_BACK);
            }

            //シーン移行時の演出が終わったら
            if (!titleSound->IsPlaying(SoundTag::Start))
            {
                if (!titleBlend->NowFade())
                {
                    //すべてのサウンドを止める
                    titleSound->StopAllSound();

                    //管理クラス内の確保したデータ解放
                    AssetManager::ReleaseAllAsset();
                    ObjManager::ReleaseAllObj();

                    if (type == PLAY)
                    {
                        //PLAY選択時、シーンを次の場面にする
                        return new RoomScene;
                    }
                    if (type == LOAD)
                    {
                        //LOAD選択時、シーンを保存シーンにする
                        return SaveScene::Load();
                    }
                }
            }
        }
    }

    return this;
}

// 描画処理 //

void TitleScene::Draw()
{
    //オブジェクト描画
    ObjManager::Draw();

    //選択ボタン描画
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screenGraph);
    DrawExtendGraph(BgX, BgY, BgX + 450, BgY + 200, BgHandle, true);
    for (auto type : selectTypeAll)
    {
        if (select[type])
        {
            select[type]->Draw();
        }
    }

    //フェード処理
    titleBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    titleBlend->NoBlend();
}
