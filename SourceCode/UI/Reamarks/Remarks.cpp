#include "Remarks.h"


// @brief Remarksコンストラクタ //

Remarks::Remarks(TextType texttype)
    :ObjectBase(ObjectTag::UI)
    ,textType(texttype)
    ,stringBuf()
    ,textX(0)
    ,textY(0)
    ,Sn(0)
    ,Sp(0)
    ,eofFlag(false)
    ,waitKey(false)
    ,holdBuf()
{
    SetFontSize(TEXTSIZE);          //フォントサイズ設定
}

// @brief Remarksデストラクタ //

Remarks::~Remarks()
{

}

// @brief Remarks更新処理 //

void Remarks::Update(float deltaTime)
{
    //～終了フラグが立っていなかったら～
    if (!eofFlag)
    {
        //～待機フラグが立っていたら～
        if (waitKey)
        {
            //～マウスの左クリックが押されたら～
            if ((GetMouseInput() & MOUSE_INPUT_LEFT))
            {
                waitKey = false;                                                    //待機フラグをfalseにする
            }
        }
        //～待機フラグが立っていなかったら～
        else
        {
            char Moji = GetText(Sn, Sp);                                            //1文字分取得
            switch (Moji)
            {
                //～待機文字だったら～
            case '/':
                waitKey = true;                                                     //待機フラグを立てる
                Sp++;                                                               //読み込み文字を1文字進める
                break;

                //～終了文字だったら～
            case '^':
                eofFlag = true;                                                     //終了フラグを立てる
                Sp++;                                                               //読み込み文字を1文字進める
                break;

                //～クリア文字だったら～
            case '|':
                for (int i = 0; i < BUFHEIGHT; i++)
                {
                    for (int j = 0; j < BUFWIDTH; j++)
                    {
                        stringBuf[i][j] = 0;                                        //仮想テキストバッファを初期化
                    }
                }
                textX = 0;                                                          //描画位置X初期化
                textY = 0;                                                          //描画位置Y初期化
                Sp++;                                                               //読み込み文字を1文字進める
                break;

                //～その他の文字～
            default:
                //---1文字分記憶する---//
                holdBuf[0] = GetText(Sn, Sp);
                holdBuf[1] = GetText(Sn, Sp + 1);
                holdBuf[2] = '\0';

                //---テキストバッファに代入---//
                stringBuf[textY][textX * 2] = holdBuf[0];
                stringBuf[textY][textX * 2 + 1] = holdBuf[1];

                Sp += 2;                                                            //読み込み文字を2文字進める
                textX++;                                                            //文字表示位置を1文字進める

                //～文字表示位置が横幅からはみ出たら～
                if (textX > BUFWIDTH)
                {
                    NewLine();                                                      //改行する
                }

                //～読み込み文字が終端まで行ったら～
                if (GetText(Sn, Sp) == '\0')
                {
                    NewLine();                                                      //改行する
                    Sn++;                                                           //読み込み文字を1列進める
                    Sp = 0;                                                         //読み込み文字を初めからにする
                }

                break;
            }
        }
    }
    if (eofFlag)
    {
        isAlive = false;
    }
}

// @brief 文字列取得処理 //

char Remarks::GetText(int sn,int sp)
{
    char Opening[][256] =
    {
        "最近仕事がうまくいかない...。 /",
        "|いつも自分を支えてくれた妻を事故で無くし、",
        "それからずっと、自分の生きる意味を見出せないでいる。/",
        "もっと妻と触れ合っていれば良かったと、/心底思う。/",
        "|きっと私は、あの時の事をずっと引きずっているのだろう...。 /^",
    };
    char Day1Stage[][256] =
    {
        "ここは一体...。 /",
        "さっきまで自室で寝ていたはずだが? /",
        "|夢にしては感覚がしっかりしている...。 /",
        "|気味が悪いが、進むしかないのだろうか? /^",
    };
    char ManSpeak[][256] =
    {
        "あなた「なあ、/ここで何をしている?/ここは一体何なんだ？」/",
        "|男性「...。」/",
        "|男性「ここは、/過去に囚われているものが集まる場所だよ。/」",
        "|あなた「...?/どういう意味なんだ?/疲労でこんな夢を見てるってことか?」/",
        "|男性「ここには過去のせいで前に進めない人がよく呼ばれる。/多分ヤツが呼んでるんだと俺は思う。」/",
        "|あなた「ヤツ?」",
        "|男性「俺には時間がない、/ヤツに捕まってしまったからな。/",
        "ヤツにつかまって夢から覚めると、/翌日には皆謎の死を遂げている。」/",
        "|あなた「...よくわからない、一体どうすればいい?」/",
        "|男性「3日間、/とにかくヤツから逃げ切るんだ...。/",
        "....!?/ヤツが来る!/俺はもうここまでだ、早くここから離れるんだ!」/",
        "|あなた「とにかく逃げればいいんだな?/わかった...。」/",
        "ここは夢のはずなのに、/なぜかあの男性の言う通りにしなければいけない気がした。/^",
    };

    switch (textType)
    {
    //～TextTypeがOpeningTextだったら～
    case TextType::OpeningText:
        return Opening[sn][sp];                                                     //Openingの文字列を返す
        break;
    //～TxtTypeがDay1Stageだったら～
    case TextType::Day1Stage:
        return Day1Stage[sn][sp];
        break;
        //～TxtTypeがManSpeakだったら～
    case TextType::ManSpeak:
        return ManSpeak[sn][sp];
        break;
    }

    return -1;
}

// @brief 改行処理 //

void Remarks::NewLine()
{
    textY++;                                                                        //文字表示列を1列進める
    textX = 0;                                                                      //文字表示位置を初期位置にする

    //～読み込み文字の列が縦幅からはみ出るなら～
    if (textY >= BUFHEIGHT)
    {
        for (int i = 1; i < BUFHEIGHT; i++)
        {
            for (int j = 0; j < BUFWIDTH * 2; j++)
            {
                stringBuf[i - 1][j] = stringBuf[i][j];                              //テキストバッファを縦スクロールする
            }
        }

        textY--;                                                                    //文字表示列を1れつずらす
    }
}

// @brief Remarks描画処理 //

void Remarks::Draw()
{
    for (int i = 0; i < BUFHEIGHT; i++)
    {
        DrawString(i + 500, i * TEXTSIZE + 500, stringBuf[i], GetColor(255, 255, 255));     //テキストバッファの描画
    }
}