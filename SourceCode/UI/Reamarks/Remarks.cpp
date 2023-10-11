#include "Remarks.h"

#include"../../Asset/AssetManager/AssetManager.h"
#include"../../BlendMode/BlendMode.h"

// コンストラクタ //

Remarks::Remarks(TextType texttype)
    :UIBase(ObjTag::Remarks)
    , textType(texttype)
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

    canClick = true;
}

// デストラクタ //

Remarks::~Remarks()
{
    //画像ハンドル削除
    if (objHandle)
    {
        DeleteGraph(objHandle);
    }
}

// 更新処理 //

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

// 文字列取得処理 //

char Remarks::GetText(int sn, int sp)
{
    //オープニング
    char Opening[][256] =
    {
        "最近仕事がうまくいかない...。 ",
        "/|いつも自分を支えてくれた妻を事故で無くし、 ",
        "それからずっと、自分の生きる意味を見出せないでいる。 ",
        "/もっと妻と触れ合っていれば良かったと、/心底思う。 ",
        "/|きっと私は、あの時の事をずっと引きずっているのだろう...。 ",
        "/^",
    };

    //ステージ
    char Stage[][256] =
    {
        "ここは一体...。 ",
        "/さっきまで自室で寝ていたはずだが? ",
        "/|夢にしては感覚がしっかりしている...。 ",
        "/|気味が悪いが、進むしかないのだろうか? ",
        "/^ ",
    };

    //男性セリフ
    char ManSpeak[][256] =
    {
        "男性「...!?」 ",
        "/|男性「なぜ君はここにいる!」 ",
        "/|答えようとしたが声が出せない、/夢だからだろうか? ",
        "/今は彼の話を聞くことしかできないようだ。 ",
        "/|男性「ここは、/過去に囚われているものが集まる場所。」 ",
        "/男性「過去のせいで前に進めない人がよく呼ばれる。 ",
        "/多分アイツが呼んでいるんだと俺は思う。」 ",
        "/|男性「君もアイツに呼ばれてここにいるはずだ。」 ",
        "/男性「いいか? /ここでアイツに捕まったら最期、 ",
        "/翌日には皆謎の死を遂げている。」 ",
        "/|男性「とにかくヤツから逃げ切るんだ。 ",
        "/そうすれば、アイツから解放される。」 ",
        "/|男性「....!?/まずい、アイツが来る! /俺はもうここまでだ、 ",
        "/ライトをやるから、早くここから逃げるんだ!」 ",
        "/^ ",
    };

    //クリア
    char GameClear[][256] =
    {
        "扉を抜けるとき、妻の声が聞こえた気がした。 ",
        "/もしかしたら、ずっとそばにいてくれていたのかもしれない。 ",
        "/|あの夢から、自分は大切なことに気付いたんだ。",
        "/|「ありがとう、/もう一人でも大丈夫だよ。 ",
        "/いつか会いに行くまで/見守っていてほしい。」 ",
        "/|それから、/今日まで充実した日々を送ることが出来ている。 ",
        "/|君がそばにいてくれたから、/ずっと支えてくれたから...。  ",
        "/^",
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

    return -1;
}

// 改行処理 //

void Remarks::NewLine()
{
    //改行して表示位置を左端からにする
    textY++;
    textX = 0;
}

// テキストボックス //
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

// 描画処理 //

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