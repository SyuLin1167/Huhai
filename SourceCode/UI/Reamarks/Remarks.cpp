#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Remarks.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../BlendMode/BlendMode.h"

/// <summary>
/// コンストラクタ
/// </summary>
    /// <param name="type">:テキスト種類</param>
Remarks::Remarks(TextType type)
    :UIBase(ObjTag::Remarks)
    , textType(type)
    , stringBuf{}
    , holdBuf{}
    , stringNum(0)
    , stringPtr(0)
    , eofFlag(false)
    , waitKey(false)
    , textX(0)
    , textY(0)
    , textBox{}
{
    //テキストボックス設定
    objHandle =AssetManager::GetGraph("../Assets/BackGround/Remarks.png");
    objPos = VGet(0.0f, 600.0f, 0.0f);

    //ファイル読み込み
    std::ifstream ifs("../SourceCode/UI/Remarks/RemarksData.json");

    //ファイル解析
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();

    canClick = true;
}

/// <summary>
/// デストラクタ
/// </summary>
Remarks::~Remarks()
{
    //画像ハンドル削除
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void Remarks::Update(float deltaTime)
{
    //文字の読み込み中なら
    if (!eofFlag)
    {
        //待機中なら
        if (waitKey)
        {
            //左クリックが押されるまで待機
            MouseClick();
            if (hasMauseClick)
            {
                waitKey = false;
            }
        }
        else
        {
            //待機中でなければ台詞を一文字ずつ読み込む
            char Moji = GetText(stringNum, stringPtr).c_str();
            switch (Moji)
            {
            case '/':
                //待機文字だったら待機中にする
                waitKey = true;

                //読み込み文字を1文字進める
                stringPtr++;
                break;

            case '^':
                //終了文字だったら文字読み込みを終了する
                eofFlag = true;
                break;

            case '|':
                //クリア文字だったら既に表示されている文字列を消す
                for (int i = 0; i < BUFHEIGHT; i++)
                {
                    for (int j = 0; j < BUFWIDTH; j++)
                    {
                        //仮想テキストバッファ初期化
                        stringBuf[i][j] = 0;
                    }
                }

                //描画位置初期化
                textX = 0;
                textY = 0;

                //読み込み文字を1文字進める
                stringPtr++;
                break;

            default:
                //その他の文字だったら
                //1文字分記憶
                holdBuf[0] = GetText(stringNum, stringPtr);
                holdBuf[1] = GetText(stringNum, stringPtr + 1);
                holdBuf[2] = '\0';

                //テキストバッファに記憶した文字を代入
                stringBuf[textY][textX * 2] = holdBuf[0];
                stringBuf[textY][textX * 2 + 1] = holdBuf[1];

                //読み込み文字を2文字分進める
                stringPtr += 2;

                //文字表示位置を1文字進める
                textX++;

                //文字表示位置が横幅からはみ出たら改行
                if (textX > BUFWIDTH)
                {
                    NewLine();
                }

                //文が最後まで読み込み終わったら改行して次の文を読み込む
                if (GetText(stringNum, stringPtr) == '\0')
                {
                    NewLine();
                    stringNum++;
                    stringPtr = 0;
                }
                break;
            }
        }
    }
    if (eofFlag)
    {
        //台詞が読み終わったらオブジェクト削除のため死亡にする
        isAlive = false;
    }
}

/// <summary>
/// 文字列取得処理
/// </summary>
/// <param name="sn">:文字列番号</param>
/// <param name="sp">:文字ポインタ</param>
/// <returns>指定場所の文字</returns>
std::string Remarks::GetText(int sn, int sp)
{
    //オープニング
    auto& opening = doc["opening"];
    std::string Opening[][256] =
    {
        opening.GetArray()[0].GetString(),
        opening.GetArray()[1].GetString(),
        opening.GetArray()[2].GetString(),
        opening.GetArray()[3].GetString(),
        opening.GetArray()[4].GetString(),
        opening.GetArray()[5].GetString(),
    };

    //ステージ
    auto& stage = doc["stage"];
    std::string Stage[][256] =
    {
        stage.GetArray()[0].GetString(),
        stage.GetArray()[1].GetString(),
        stage.GetArray()[2].GetString(),
        stage.GetArray()[3].GetString(),
        stage.GetArray()[4].GetString(),
    };

    //男性セリフ
    auto& manSpeak = doc["manspeak"];
    std::string ManSpeak[][256] =
    {
        manSpeak.GetArray()[0].GetString(),
        manSpeak.GetArray()[1].GetString(),
        manSpeak.GetArray()[2].GetString(),
        manSpeak.GetArray()[3].GetString(),
        manSpeak.GetArray()[4].GetString(),
        manSpeak.GetArray()[5].GetString(),
        manSpeak.GetArray()[6].GetString(),
        manSpeak.GetArray()[7].GetString(),
        manSpeak.GetArray()[8].GetString(),
        manSpeak.GetArray()[9].GetString(),
        manSpeak.GetArray()[10].GetString(),
        manSpeak.GetArray()[11].GetString(),
        manSpeak.GetArray()[12].GetString(),
        manSpeak.GetArray()[13].GetString(),
        manSpeak.GetArray()[14].GetString(),
    };

    //クリア
    auto& clear = doc["clear"];
    std::string GameClear[][256] =
    {
        clear.GetArray()[0].GetString(),
        clear.GetArray()[1].GetString(),
        clear.GetArray()[2].GetString(),
        clear.GetArray()[3].GetString(),
        clear.GetArray()[4].GetString(),
        clear.GetArray()[5].GetString(),
        clear.GetArray()[6].GetString(),
        clear.GetArray()[7].GetString(),
    };

    //タイプに合わせたセリフの文字を返す
    switch (textType)
    {
    case TextType::Opening:
        return Opening[sn][sp];
        break;
    case TextType::Stage:
        return Stage[sn][sp];
        break;
    case TextType::ManSpeak:
        return ManSpeak[sn][sp];
        break;
    case TextType::GameClear:
        return GameClear[sn][sp];
        break;
    }

    return "";
}

/// <summary>
/// 改行処理
/// </summary>
void Remarks::NewLine()
{
    //改行して表示位置を左端からにする
    textY++;
    textX = 0;
}

/// <summary>
/// テキストボックス
/// </summary>
/// <param name="lx">:左上座標</param>
/// <param name="ly">:左上座標</param>
/// <param name="rx">:右下座標</param>
/// <param name="ry">:右下座標</param>
void Remarks::TextBox(int lx, int ly, int rx, int ry)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    //値が変わらないものを一通り設定
    for (int i = 0; i < 6; i++)
    {
        textBox[i].pos.z = 0.0f;
        textBox[i].rhw = 1.0f;
        textBox[i].dif = VERTEX_COLOR;
        textBox[i].u = UV;
        textBox[i].v = UV;
    }


    //頂点情報
    textBox[0].pos.x = textBox[2].pos.x = (float)lx;
    textBox[0].pos.y = textBox[1].pos.y = (float)ly;

    textBox[3].pos.x = textBox[1].pos.x = (float)rx;
    textBox[3].pos.y = textBox[2].pos.y = (float)ry;
    textBox[3].dif.a = textBox[2].dif.a = 255;

    //同じ頂点はコピー
    textBox[4] = textBox[2];
    textBox[5] = textBox[1];

}

/// <summary>
/// 描画処理
/// </summary>
void Remarks::Draw()
{
    ChangeFont("MS ゴシック", DX_CHARSET_DEFAULT);

    //テキストボックス描画
    SetFontSize(TEXTSIZE);
    DrawBox(0, BOUNDARY_POS_RY, SCREEN_WIDTH, SCREEN_HEIGHT, TEXTBOX_COLOR, TRUE);
    TextBox(0, BOUNDARY_POS_LY, SCREEN_WIDTH, BOUNDARY_POS_RY);
    DrawPolygon2D(textBox, 2, DX_NONE_GRAPH, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    //台詞描画
    for (int i = 0; i < BUFHEIGHT; i++)
    {
        DrawString(i + FIRST_TEXT_POS_X, i * TEXTSIZE + FIRST_TEXT_POS_Y, stringBuf[i], WHITE_TEXT_COLOR);
    }

    //待機アイコン描画
    if (waitKey)
    {
        DrawString(WAIT_ICON_X, WAIT_ICON_Y, "▽", WHITE_TEXT_COLOR);
    }
}