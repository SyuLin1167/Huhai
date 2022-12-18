#pragma once

#include<DxLib.h>
#include<string>
#include<unordered_map>

using namespace std;

/* Animationのクラス */
class Animation
{
public:
	/// <summary>
	/// Animationコンストラクタ―
	/// </summary>
	Animation(int modelHandle);

	/// <summary>
	/// Animationデストラクタ―
	/// </summary>
	~Animation();

	/// <summary>
	/// アニメーション追加処理
	/// </summary>
	/// <param name="fileName">:ファイル名</param>
	/// <param name="animFps">:再生フレームレート(デフォルト・30fps)</param>
	/// <param name="animLoop">:ループ再生(デフォルト・ループさせる)</param>
	/// <returns></returns>
	int AddAnimation(string animFileName, float animFps = 30.0f, bool animLoop = true);

	/// <summary>
	/// アニメーション時間セット
	/// </summary>
	/// <param name="deltaTime">:フレームレート</param>
	void AddAnimTime(float deltaTime);

	/// <summary>
	/// アニメーション再生
	/// </summary>
	/// <param name="animId">:アニメーションID</param>
	void StartAnim(int animID);

	/// <summary>
	/// アニメーション停止
	/// </summary>
	void StopAnim();

	/// <summary>
	/// 再生中かどうか
	/// </summary>
	/// <returns>再生状態</returns>
	bool IsPlaying();

	/* アニメーション１個分のデータ構造体 */
	struct AnimData
	{
		int animHandle;			//アニメーションハンドル
		int animIndex;			//アタッチするアニメーション番号
		float totalTime;		//総再生時間
		float animFps;			//再生速度
		bool isLoop;			//ループ再生するかどうか
	};
private:
	int modelHandle;			//モデルハンドル
	vector<AnimData> animData;	//アニメーション複数登録用
	int nowAnimType;			//現在のアニメーションID
	int attachedIndex;			//アタッチ後のインデックス
	float nowAnimTime;			//現在のアニメーション時刻
};

