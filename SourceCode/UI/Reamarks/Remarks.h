#pragma once
#include"../../Object/ObjectBase/ObjectBase.h"
#include"TextType.h"

constexpr int TEXTSIZE = 24;
constexpr int BUFWIDTH = 50;
constexpr int BUFHEIGHT = 20;

        /*Remarksのクラス*/
class Remarks :public ObjectBase
{
public:
    /// <summary>
    /// Remarksコンストラクタ
    /// </summary>
    /// <param name="texttype">:テキストの種類</param>
    Remarks(TextType texttype);

    /// <summary>
    /// Remarksデストラクタ
    /// </summary>
    ~Remarks();

    /// <summary>
    /// Remarks更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 文字列取得処理
    /// </summary>
    /// <param name="sn">:文字列番号</param>
    /// <param name="sp">:文字ポインタ</param>
    /// <returns>指定場所の文字</returns>
    char GetText(int sn, int sp);

    /// <summary>
    /// 改行処理
    /// </summary>
    void NewLine();

    /// <summary>
    /// Remarks描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// Remarks終了フラグ
    /// </summary>
    /// <returns>:終了フラグ</returns>
    bool RemarksEof() { return eofFlag; }

private:
    TextType textType;
    char stringBuf[BUFHEIGHT][BUFWIDTH * 2 + 1];        //仮想テキストバッファ
    int textX;                                          //文字表示位置X
    int textY;                                          //文字表示位置Y
    int Sn;                                             //文字列番号
    int Sp;                                             //文字ポインタ
    bool eofFlag;                                       //終了フラグ
    bool waitKey;                                       //待機フラグ
    char holdBuf[3];                                    //文字一時記憶領域
    int graph;
};