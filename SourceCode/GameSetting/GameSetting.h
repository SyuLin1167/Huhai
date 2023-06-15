#pragma once

/*GameSettingクラス*/
class GameSetting
{
public:
    /// <summary>
    /// 初期化処理
    /// </summary>
    static int Init();

    /// <summary>
    /// 後処理
    /// </summary>
    static void Finalize();
private:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    GameSetting() {};

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameSetting() {};
	
    //自身へのインスタンス
    static GameSetting* gameSetting;
};

