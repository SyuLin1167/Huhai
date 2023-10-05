#pragma once

#include"../../GameSetting/GameSetting.h"
#include"../UIBase/UIBase.h"
#include"TextType.h"

constexpr int TEXTSIZE = 24;        //テキストサイズ
constexpr int BUFWIDTH = 50;        //表示制限行
constexpr int BUFHEIGHT = 20;       //表示制限列

/*Remarksクラス*/
class Remarks :public UIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="type">:テキストの種類</param>
    Remarks(TextType type);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Remarks();

    /// <summary>
    /// 更新処理
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
    /// テキストボックス
    /// </summary>
    void TextBox(int lx,int ly,int rx,int ry);

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// 終了フラグ
    /// </summary>
    /// <returns>:終了する:true|しない:false</returns>
    bool RemarksEof() { return eofFlag; }

private:
    TextType textType;
    char stringBuf[BUFHEIGHT][BUFWIDTH * 2 + 1];        //仮想テキストバッファ
    char holdBuf[3];                                    //文字一時記憶領域
    int Sn;                                             //文字列番号
    int Sp;                                             //文字ポインタ

    const int WHITE_TEXT_COLOR;                         //テキスト色(ホワイト)
    const int WAIT_ICON_X = SCREEN_WIDTH * 8 / 10;      //待機アイコン座標X
    const int WAIT_ICON_Y = SCREEN_HEIGHT * 9 / 10;      //待機アイコン座標Y

    bool eofFlag;                                       //終了フラグ
    bool waitKey;                                       //待機フラグ

    int textX;                                          //文字表示位置X
    int textY;                                          //文字表示位置Y

    VERTEX2D textBox[6];                                //テキストボックスポリゴン
    const int BOUNDARY_POS_Y = 950;                     //ポリゴンとボックスの境界線座標
    COLOR_U8 color = { 20,0,0,0 };      //頂点の色
};