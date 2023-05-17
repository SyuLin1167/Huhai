#pragma once

#include<DxLib.h>
#include<vector>
#include<string>

using namespace std;

/*Model�̃N���X*/
class Model
{
public:
    /// <summary>
    /// Model�R���X�g���N�^
    /// </summary>>
    Model() {};

    /// <summary>
    /// Model�f�X�g���N�^
    /// </summary>
    ~Model() {};

    /// <summary>
    /// ���f���ǉ�����
    /// </summary>
    /// <param name="modelFileName">:���f���t�@�C����</param>
    /// <returns></returns>
    int AddModel(string modelFileName);

    /// <summary>
    /// Model�ݒ菈��
    /// </summary>
    /// <param name="modelId">:���f��ID</param>
    /// <returns>���f���n���h��</returns>
    int SetModel(int modelId);

    /*���f��1���̃f�[�^�\����*/
    struct ModelData
    {
    public:
        /// <summary>
        /// ModelData�R���X�g���N�^
        /// </summary>
        ModelData();

        int modelHandle;        //���f���f�[�^�n���h��
    };

private:
    vector<ModelData> modelData;
};

