#pragma once
#include <Dxlib.h>

const int ScreenWidth = 1920;		//スクリーン幅指定
const int ScreenHeight = 1080;		//スクリーン高さ指定
//---スクリーンサイズの例: 640*480, 800*600, 1024*768, 1280*1024, 1280*720, 1920*1080---//

const int ColorBit = 16;			//カラービット数
//---カラービット数の例: 16, 32---//

/*SceneBaseのクラス*/
class SceneBase
{
public:
	/// <summary>
	/// コンストラクタ―
	/// </summary>
	SceneBase();

	/// <summary>
	/// デストラクタ―
	/// </summary>
	virtual ~SceneBase();

	/// <summary>
	/// Scene更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <returns>現在のシーンのポインタ</returns>
	virtual SceneBase* Update(float deltaTime) = 0;

	/// <summary>
	/// シーンの描画
	/// </summary>
	virtual void Draw() = 0;

protected:
	int BgHandle;		//背景画像ハンドル
	int BgX;			//背景座標X
	int BgY;			//背景座標Y
};

