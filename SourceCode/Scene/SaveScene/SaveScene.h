#pragma once

#include"../SceneBase/SceneBase.h"

/*SaveScene�N���X*/
class SaveScene
{
public:
    /// <summary>
    /// �C���X�^���X��������
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �Z�[�u����
    /// </summary>
    /// <param name="nowScene">:�ۑ�����V�[��</param>
    static void Save(SceneBase* nowScene);
	
    /// <summary>
    /// ���[�h����
    /// </summary>
    /// <returns>:�Z�[�u�V�[��</returns>
    static SceneBase* Load();

    /// <summary>
    /// �㏈��
    /// </summary>
    static void Finalize();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SaveScene();
private:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    SaveScene();

    static std::unique_ptr<SaveScene> saveScene;        //���g�̎���
    std::unique_ptr<SceneBase> scene;                   //�Z�[�u�V�[��
};

