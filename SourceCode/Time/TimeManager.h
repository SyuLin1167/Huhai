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
    /// DeltaTime取得処理
    /// </summary>
    /// <returns>deltaTime</returns>
    const float DeltaTime();

private:
    float nowTime;      //現在の時間
    float prevTime;     //過去の時間
    float deltaTime;    //フレームレート
};

