#pragma once

#include<vector>
#include<string>

/*Model�N���X*/
class Model
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>>
    Model();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Model();

    /// <summary>
    /// �ǉ�����
    /// </summary>
    /// <param name="fileName">:�t�@�C����</param>
    /// <returns>modelData�z��̓Y�����ԍ�</returns>
    int AddModel(std::string fileName);

    /// <summary>
    /// �ݒ菈��
    /// </summary>
    /// <param name="modelID">:���f��ID</param>
    /// <returns>���f���n���h��</returns>
    int GetModel(int modelID);

    /*���f��1���̃f�[�^�\����*/
    struct ModelData
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        ModelData();

        int modelHandle;                    //���f���n���h��
    };

private:
    std::vector<ModelData> modelData;       //���f���̃f�[�^�z��
};

