#pragma once
#include <DxLib.h>

/*TimeManagerクラス*/
class TimeManager
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TimeManager();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TimeManager();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// DeltaTime取得
    /// </summary>
    /// <returns>deltaTime</returns>
    float DeltaTime() const { return deltaTime; }

private:
    float nowTime;      //現在の時間
    float prevTime;     //過去の時間
    float deltaTime;    //フレームレート
};

