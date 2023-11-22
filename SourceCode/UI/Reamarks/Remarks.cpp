#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Remarks.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../BlendMode/BlendMode.h"
#include"../Status/Base/StatusBase.h"

Remarks::Remarks(TextType type)
    :UIBase(ObjTag::Remarks)
    , fileHandle(-1)
    , text()
    , lineCounter(0)
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
    //ファイル読み込み
    switch (type)
    {
    case TextType::Opening:
        fileHandle = FileRead_open("..//SourceCode/UI/Reamarks/RemarksData/Opening.txt");
        break;

    case TextType::Stage:
        fileHandle = FileRead_open("..//SourceCode/UI/Reamarks/RemarksData/Stage.txt");
        break;

    case TextType::ManSpeak:
        fileHandle = FileRead_open("..//SourceCode/UI/Reamarks/RemarksData/ManSpeak.txt");
        break;

    case TextType::GameClear:
        fileHandle = FileRead_open("..//SourceCode/UI/Reamarks/RemarksData/GameClear.txt");
        break;
    }

    //ファイルデータ解析
    while(FileRead_eof(fileHandle)==0)
    {
        FileRead_gets(text[lineCounter], sizeof(text[lineCounter]), fileHandle);
        lineCounter++;
    }
    FileRead_close(fileHandle);

    canClick = true;
}

Remarks::~Remarks()
{
    //処理なし
}

void Remarks::Update(const float deltaTime)
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
            char Moji = GetText(stringNum, stringPtr);
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

char Remarks::GetText(int strnnum, int strptr)
{
    return text[strnnum][strptr];
}

void Remarks::NewLine()
{
    //改行して表示位置を左端からにする
    textY++;
    textX = 0;
}

void Remarks::TextBox(int lx, int ly, int rx, int ry)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, MAX_ALPHA);

    //値が変わらないものを一通り設定
    for (int i = 0; i < MAX_VERTEX; i++)
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
    textBox[3].dif.a = textBox[2].dif.a = MAX_ALPHA;

    //同じ頂点はコピー
    textBox[4] = textBox[2];
    textBox[5] = textBox[1];

}

void Remarks::Draw()
{
    ChangeFont(msGothic, DX_CHARSET_DEFAULT);

    //テキストボックス描画
    SetFontSize(TEXTSIZE);
    DrawBox(0, BOUNDARY_POS_RY, SCREEN_WIDTH, SCREEN_HEIGHT, TEXTBOX_COLOR, TRUE);
    TextBox(0, BOUNDARY_POS_LY, SCREEN_WIDTH, BOUNDARY_POS_RY);
    DrawPolygon2D(textBox, POLYGON_NUM, DX_NONE_GRAPH, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA);

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