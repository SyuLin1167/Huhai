#pragma once
#include<DxLib.h>
#include"../SceneBase/SceneBase.h"

	/*ResultScene�N���X*/
class Result :public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Result();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Result();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <returns>���݂̃V�[���̃|�C���^</returns>
	SceneBase* Update(float deltaTime)override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw()override;

};
