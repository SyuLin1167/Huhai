#pragma once


constexpr int ColorBit = 16;                                //カラービット数

constexpr int SCREEN_WIDTH = 1920;                          //スクリーン幅
constexpr int SCREEN_HEIGHT = 1080;                         //スクリーン高さ
constexpr int SCREEN_CENTER_WIDTH = SCREEN_WIDTH / 2;       //スクリーン中心幅
constexpr int SCREEN_CENTER_HEIGHT = SCREEN_HEIGHT / 2;     //スクリーン中心高さ

/// <summary>
/// GameSettingクラス
/// </summary>
class GameSetting
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameSetting();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameSetting();

    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <returns>初期化できたかどうか</returns>
    int Init();
};

