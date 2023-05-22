#pragma once
#include"../SceneBase/SceneBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

/*�����V�[���̃N���X*/
class Room:public SceneBase
{
public:
	/// <summary>
	/// Room�R���X�g���N�^
	/// </summary>
	Room();

	/// <summary>
	/// Room�f�X�g���N�^
	/// </summary>
	~Room();

	/// <summary>
	/// Room�X�V����
	/// </summary>
	/// <param name="deltaTime">:�t���[�����[�g</param>
	/// <returns>���݂̃V�[���̃|�C���^</returns>
	SceneBase* Update(float deltaTime)override;

	/// <summary>
	/// Room�`�揈��
	/// </summary>
	void Draw()override;

private:
	class BlendMode* roomBlend;
};

