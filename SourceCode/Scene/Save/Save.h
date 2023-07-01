#pragma once

#include"../SceneBase/SceneBase.h"

/*SaveScene�N���X*/
class SaveScene
{
public:
    /// <summary>
    /// ����������
    /// </summary>
    static void Init();

    /// <summary>
    /// �Z�[�u����
    /// </summary>
    /// <param name="scene">:�V�[��</param>
    static void Save(SceneBase* scene);
	
    /// <summary>
    /// ���[�h����
    /// </summary>
    /// <returns>:�Z�[�u�V�[��</returns>
    static SceneBase* Load();

    /// <summary>
    /// �㏈��
    /// </summary>
    static void Finalize();

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SaveScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SaveScene();

    static SaveScene* save;          //���g�̎���
    SceneBase* saveScene;       //�Z�[�u�V�[��
};

