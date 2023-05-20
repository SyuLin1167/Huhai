#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

/*Day1�����V�[���̃N���X*/
class Day1Room:public SceneBase
{
public:
	/// <summary>
	/// Day1Room�R���X�g���N�^
	/// </summary>
	Day1Room();

	/// <summary>
	/// Day1Room�f�X�g���N�^
	/// </summary>
	~Day1Room();

	/// <summary>
	/// Day1Room�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	/// <returns>���݂̃V�[���̃|�C���^</returns>
	SceneBase* Update(float deltaTime)override;

	/// <summary>
	/// Day1Room�`�揈��
	/// </summary>
	void Draw()override;

private:
	class Remarks* remarks;
	class Action* action;
	class BlendMode* roomBlend;
};

