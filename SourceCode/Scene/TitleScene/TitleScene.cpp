#include "TitleScene.h"

#include "../../Object/ObjectManager/ObjManager.h"
#include "../../Asset/AssetManager/AssetManager.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include "../../UI/Select/Select.h"
#include "../RoomScene/RoomScene.h"
#include "../SaveScene/SaveScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
    :SceneBase()
{
    //タイトルロゴ生成
    bgHandle = AssetManager::GetGraph("../Assets/BackGround/Title.png");
    bgX = TITLE_POS_X;
    bgY = TITLE_POS_Y;

    //サウンド生成
    sound->AddSound("../Assets/Sound/TitleBgm.mp3", SoundTag::Title);
    sound->AddSound("../Assets/Sound/StartSE.mp3", SoundTag::Start);
    sound->StartSound(SoundTag::Title, DX_PLAYTYPE_LOOP);

    //カメラ生成
    ObjManager::AddObj(new FixedCamera);

    //マップ生成
    ObjManager::AddObj(new Map(Map::MapTag::TITLE));

    //ドア生成
    door = new Door("title");
    ObjManager::AddObj(door);

    //ライト生成
    ObjManager::AddObj(new BlinkingLight("title"));
    ObjManager::AddObj(new NomalLight("title", "1"));

    //選択ボタン生成
    for (auto type : selectTypeAll)
    {
        select[type] = new Select(type);
    }

    //グラフ作成
    screenGraph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
    //画像ハンドル削除
    if (bgHandle)
    {
        DeleteGraph(bgHandle);
    }
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
/// <returns>次のフレームのシーン</returns>
SceneBase* TitleScene::UpdateScene(const float deltaTime)
{
    //マウスポインター表示
    SetMouseDispFlag(TRUE);

    //オブジェクト更新
    ObjManager::UpdateAllObj(deltaTime);
    door->MoveAnim(Door::AnimType::OPEN);

    for (auto type : selectTypeAll)
    {
        select[type]->Update(deltaTime);

        //ボタン選択時処理
        if (select[type]->GetButtonInput())
        {
            //マウス座標を画面の中心にして非表示にする
            SetMousePoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT);
            SetMouseDispFlag(false);

            //フェードアウト
            blendMode->AddFade(deltaTime);

            //EXIT選択時、シーンをnullptrにする
            if (type == EXIT)
            {
                return nullptr;
            }
            else
            {
                //EXIT以外選択時、SEを再生
                sound->StartSoundOnce(SoundTag::Start, DX_PLAYTYPE_BACK);
            }

            //シーン移行時の演出が終わったら
            if (!sound->IsPlaying(SoundTag::Start))
            {
                if (!blendMode->NowFade())
                {
                    //すべてのサウンドを止める
                    sound->StopAllSound();

                    //管理クラス内の確保したデータ解放
                    AssetManager::ReleaseAllAsset();
                    ObjManager::DeleteAllObj();

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

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::DrawScene()
{
    //オブジェクト描画
    ObjManager::DrawAllObj();

    //選択ボタン描画
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screenGraph);
    DrawExtendGraph(bgX, bgY, bgX + TITLE_SIZE_X, bgY + TITLE_SIZE_Y, bgHandle, true);
    for (auto type : selectTypeAll)
    {
        if (select[type])
        {
            select[type]->Draw();
        }
    }

    //フェード処理
    blendMode->Fade();
    DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK_SCREEN_COLOR, true);
    blendMode->NoBlend();
}
