#include "Model.h"
#include"../../Asset/AssetManager/AssetManager.h"


// �R���X�g���N�^ //

Model::Model()
{
}

// �f�X�g���N�^ //

Model::~Model()
{
    //�f�[�^�폜
    while (modelData.size() == 0)
    {
        modelData.pop_back();
    }
}

// �ǉ����� //

int Model::AddModel(std::string modelFileName)
{
    //���b�V����o�^&�擾����
    ModelData model = {};
    model.modelHandle = AssetManager::GetMesh(modelFileName.c_str());

    //���g���󂾂����炻�̂܂ܕԂ�
    if (model.modelHandle == -1)
	{
        return model.modelHandle;
    }

    //�f�[�^�ɒǉ�����ID��Ԃ�
    modelData.emplace_back(model);
    return static_cast<int>(modelData.size() - 1);
}

// �ݒ菈�� //

int Model::GetModel(int modelID)
{
    //�f�[�^����ID�̃��f���n���h����Ԃ�
	return modelData[modelID].modelHandle;
}

// �R���X�g���N�^ //

Model::ModelData::ModelData()
	:modelHandle(-1)
{
}