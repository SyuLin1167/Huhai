#include "Remarks.h"
#include<unordered_map>

// コンストラクタ //

Remarks::Remarks(TextType texttype)
    :ObjBase(ObjectTag::Remarks)
    , textType(texttype)
    , stringBuf{}
    , holdBuf{}
    , Sn(0)
    , Sp(0)
    , eofFlag(false)
    , waitKey(false)
    , textX(0)
    , textY(0)
    , graph(MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT))
{
    //テキストボックス設定
    objHandle = LoadGraph("../Assets/BackGround/Remarks.png");
    objPos = VGet(0.0f, 600.0f, 0.0f);

    SetFontSize(TEXTSIZE);
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
            if ((GetMouseInput() & MOUSE_INPUT_LEFT))
            {
                waitKey = false;
            }
        }
        else
        {
            //待機中でなければ台詞を一文字ずつ読み込む
            char Moji = GetText(Sn, Sp);
            switch (Moji)
            {
            case '/':
                //待機文字だったら待機中にする
                waitKey = true;

                //読み込み文字を1文字進める
                Sp++;
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
                Sp++;
                break;

            default:
                //その他の文字だったら
                //1文字分記憶
                holdBuf[0] = GetText(Sn, Sp);
                holdBuf[1] = GetText(Sn, Sp + 1);
                holdBuf[2] = '\0';

                //テキストバッファに記憶した文字を代入
                stringBuf[textY][textX * 2] = holdBuf[0];
                stringBuf[textY][textX * 2 + 1] = holdBuf[1];

                //読み込み文字を2文字分進める
                Sp += 2;

                //文字表示位置を1文字進める
                textX++;

                //文字表示位置が横幅からはみ出たら改行
                if (textX > BUFWIDTH)
                {
                    NewLine();
                }

                //文が最後まで読み込み終わったら改行して次の文を読み込む
                if (GetText(Sn, Sp) == '\0')
                {
                    NewLine();
                    Sn++;
                    Sp = 0;
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
        "/もっと妻と触れ合っていれば良かったと、/心底思う。",
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
        "/|男性「3日間、 /とにかくヤツから逃げ切るんだ。 ",
        "/そうすれば、アイツから解放される。」 ",
        "/|男性「....!?/まずい、アイツが来る! /俺はもうここまでだ、 ",
        "/これを持って早くここから逃げるんだ!」  ",
        "/^ ",
    };

    //クリア
    char GameClear[][256] =
    {
        "現在プレイできるのはここまでになります。",
        "/|遊んでいただきありがとうございました!!!",
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

// 描画処理 //

void Remarks::Draw()
{
    //テキストボックス描画
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, graph);
    DrawExtendGraph((int)objPos.x, (int)objPos.y, (int)objPos.x + 1920, (int)objPos.y + 480, objHandle, TRUE);

    //台詞描画
    for (int i = 0; i < BUFHEIGHT; i++)
    {
        DrawString(i + 620, i * TEXTSIZE + 930, stringBuf[i], GetColor(255, 255, 255));
    }
}