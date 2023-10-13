#pragma once

#include"../../GameSetting/GameSetting.h"
#include"../UIBase/UIBase.h"
#include"TextType.h"

constexpr int TEXTSIZE = 24;        //テキストサイズ
constexpr int BUFWIDTH = 50;        //表示制限行
constexpr int BUFHEIGHT = 20;       //表示制限列

/// <summary>
/// Remarksクラス
/// </summary>
class Remarks :public UIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="type">:テキスト種類</param>
    Remarks(TextType type);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Remarks();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// 文字列取得処理
    /// </summary>
    /// <param name="strnnum">:文字列番号</param>
    /// <param name="strptr">:文字ポインタ</param>
    /// <returns>指定場所の文字</returns>
    char GetText(int strnum, int strptr);

    /// <summary>
    /// 改行処理
    /// </summary>
    void NewLine();

    /// <summary>
    /// テキストボックス
    /// </summary>
    /// <param name="lx">:左上座標</param>
    /// <param name="ly">:左上座標</param>
    /// <param name="rx">:右下座標</param>
    /// <param name="ry">:右下座標</param>
    void TextBox(int lx,int ly,int rx,int ry);

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

    /// <summary>
    /// 終了フラグ
    /// </summary>
    /// <returns>:終了する:true|しない:false</returns>
    bool RemarksEof() { return eofFlag; }

private:
    int fileHandle;                                     //ファイルハンドル
    char text[256][256];                              //テキスト
    int lineCounter;                                    //行カウンター

    char stringBuf[BUFHEIGHT][BUFWIDTH * 2 + 1];        //仮想テキストバッファ
    char holdBuf[3];                                    //文字一時記憶領域
    int stringNum;                                      //文字列番号
    int stringPtr;                                      //文字ポインタ

    const int WHITE_TEXT_COLOR= GetColor(240, 240, 240);//テキスト色(ホワイト)
    const int WAIT_ICON_X = SCREEN_WIDTH * 8 / 10;      //待機アイコン座標X
    const int WAIT_ICON_Y = SCREEN_HEIGHT * 9 / 10;     //待機アイコン座標Y

    bool eofFlag;                                       //終了フラグ
    bool waitKey;                                       //待機フラグ

    const int FIRST_TEXT_POS_X = 620;                   //テキスト初期座標X
    const int FIRST_TEXT_POS_Y = 930;                   //テキスト初期座標Y
    int textX;                                          //文字表示位置X
    int textY;                                          //文字表示位置Y

    VERTEX2D textBox[6];                                //テキストボックスポリゴン
    const int BOUNDARY_POS_LY = 750;                    //ポリゴンとボックスの境界線左上座標
    const int BOUNDARY_POS_RY = 950;                    //ポリゴンとボックスの境界線右下座標
    const float UV = 0;                                 //uv
    COLOR_U8 VERTEX_COLOR = { 20,0,0,0 };               //頂点の色
    const int TEXTBOX_COLOR = GetColor(0, 0, 20);       //テキストボックスの色
};