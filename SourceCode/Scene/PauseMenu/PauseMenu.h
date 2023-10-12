#pragma once
#include<unordered_map>
#include<string>

#include"../../Scene/SceneBase/SceneBase.h"

/// <summary>
/// PauseMenuクラス
/// </summary>
class PauseMenu:public SceneBase
{
public:
    /// <summary>
    /// インスタンス生成処理
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// ポーズメニューのインスタンス取得処理
    /// </summary>
    /// <returns>ポーズメニュー</returns>
    static SceneBase* GetPauseMenuInstance();

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
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    /// <returns>次フレームのシーン</returns>
    SceneBase* UpdateScene(float deltaTime) override;

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
    /// 描画処理
    /// </summary>
    void DrawScene()override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PauseMenu();

private:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    PauseMenu();

    static std::unique_ptr<PauseMenu> pauseMenu;                        //自身の実態

    const int PIXEL_WIDTH = 8;                                          //ピクセル幅
    const int GAUSS_PARAM = 1400;                                       //ぼかし値

    std::unordered_map<std::string, class Button*> buttonData;          //ボタンデータ
    std::unordered_map<std::string, class ParamButton*> paramData;      //パラメーターデータ

    class TitleButton* titleButton;                                     //タイトルボタン
};

