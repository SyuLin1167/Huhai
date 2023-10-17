#pragma once
#include<unordered_map>
#include<string>
#include<memory>

#include"ButtonName.h"

/// <summary>
/// PauseMenuクラス
/// </summary>
class PauseMenu
{
public:
    /// <summary>
    /// インスタンス生成処理
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// ボタン追加処理
    /// </summary>
    /// <param name="name">:登録名</param>
    void AddButton(std::string name);


    /// <summary>
    /// パラメーター追加処理
    /// </summary>
    /// <param name="name">:登録名</param>
    /// <param name="value">:パラメーター初期値</param>
    void AddParam(std::string name,int value);

    /// <summary>
    /// ステータス状態
    /// </summary>
    /// <param name="name">:ボタン名</param>
    /// <returns>オン:true|オフ:false</returns>
    static bool HasStatus(std::string name);

    /// <summary>
    /// タイトル移動
    /// </summary>
    /// <returns>移動する:true|しない:false</returns>
    static bool BackToTitle();

    /// <summary>
    /// パラメーター取得
    /// </summary>
    /// <param name="name">:パラメーター名</param>
    /// <returns>:パラメーター</returns>
    static int Parameter(std::string name);

    /// <summary>
    /// タイトルボタンリセット
    /// </summary>
    static void ResetTitleButton();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    static void Update(const float deltaTime);

    /// <summary>
    /// 描画処理
    /// </summary>
    static void Draw();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PauseMenu();
private:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    PauseMenu();

    const std::string fontName = "KillingFont";                         //フォント名

    const int FIRST_SOUND_PARAM = 150;                                  //音量初期値

    const int FIRST_BRIGHT_PARAM = 60;                                  //明るさ初期値
    const int MAX_BRIGHT_PARAM = 75;                                    //明るさ最大値
    const int MIN_BRIGHT_PARAM = 10;                                    //明るさ最小値

    const int FIRST_SENSITIVITY = 220;                                  //感度初期値
    const int MAX_SENSITIVITY = 245;                                    //感度最大値
    const int MIN_SENSITIVITY = 60;                                     //感度最小値

    static std::unique_ptr<PauseMenu> pauseMenu;                        //自身の実態

    std::unordered_map<std::string, class Button*> buttonData;          //ボタンデータ
    std::unordered_map<std::string, class ParamButton*> paramData;      //パラメーターデータ

    class TitleButton* titleButton;                                     //タイトルボタン
};

