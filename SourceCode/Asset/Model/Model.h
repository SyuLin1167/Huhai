#pragma once

#include<DxLib.h>
#include<vector>
#include<string>

using namespace std;

/*Modelのクラス*/
class Model
{
public:
    /// <summary>
    /// Modelコンストラクタ
    /// </summary>>
    Model() {};

    /// <summary>
    /// Modelデストラクタ
    /// </summary>
    ~Model() {};

    /// <summary>
    /// モデル追加処理
    /// </summary>
    /// <param name="modelFileName">:モデルファイル名</param>
    /// <returns></returns>
    int AddModel(string modelFileName);

    /// <summary>
    /// Model設定処理
    /// </summary>
    /// <param name="modelId">:モデルID</param>
    /// <returns>モデルハンドル</returns>
    int SetModel(int modelId);

    /*モデル1個分のデータ構造体*/
    struct ModelData
    {
    public:
        /// <summary>
        /// ModelDataコンストラクタ
        /// </summary>
        ModelData();

        int modelHandle;        //モデルデータハンドル
    };

private:
    vector<ModelData> modelData;
};

