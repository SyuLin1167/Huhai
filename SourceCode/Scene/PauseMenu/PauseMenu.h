#pragma once
#include<unordered_map>
#include<string>

#include"../../Scene/SceneBase/SceneBase.h"

/*PauseMenuクラス*/
class PauseMenu:public SceneBase
{
public:
    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <param name="screen">:ゲーム画面</param>
    static SceneBase* Init();

    /// <summary>
    /// 後処理
    /// </summary>
    static void Finalize();

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
    SceneBase* Update(float deltaTime) override;

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
    void Draw()override;

private:
    /// <summary>
    /// コンストラクタ(シングルトン)
    /// </summary>
    PauseMenu();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~PauseMenu();

    static PauseMenu* pause;        //自身の実態

    std::unordered_map<std::string, class Button*> buttonData;      //ボタンデータ
    std::unordered_map<std::string, class ParamButton*> paramData;      //パラメーターデータ

    class TitleButton* titleButton;         //タイトルボタン
};

