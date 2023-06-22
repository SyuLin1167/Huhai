#pragma once

#include<vector>
#include<string>

/*Modelクラス*/
class Model
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>>
    Model();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Model();

    /// <summary>
    /// 追加処理
    /// </summary>
    /// <param name="fileName">:ファイル名</param>
    /// <returns>modelData配列の添え字番号</returns>
    int AddModel(std::string fileName);

    /// <summary>
    /// 設定処理
    /// </summary>
    /// <param name="modelID">:モデルID</param>
    /// <returns>モデルハンドル</returns>
    int GetModel(int modelID);

    /*モデル1個分のデータ構造体*/
    struct ModelData
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ModelData();

        int modelHandle;                    //モデルハンドル
    };

private:
    std::vector<ModelData> modelData;       //モデルのデータ配列
};

