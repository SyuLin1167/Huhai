#pragma once

//カラービット数
constexpr int ColorBit = 16;

constexpr auto SCREEN_WIDTH = 1920;       //スクリーン幅
constexpr auto SCREEN_HEIGHT = 1080;      //スクリーン高さ

/*GameSettingクラス*/
class GameSetting
{
public:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    GameSetting() {};

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameSetting() { Finalize(); }

    /// <summary>
    /// 初期化処理
    /// </summary>
    int Init();

    /// <summary>
    /// 後処理
    /// </summary>
    void Finalize();
};

