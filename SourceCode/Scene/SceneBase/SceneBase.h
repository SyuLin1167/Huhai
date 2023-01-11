#pragma once
#include <Dxlib.h>

const int ColorBit = 16;			//�J���[�r�b�g��
//---�J���[�r�b�g���̗�: 16, 32---//

/*SceneBase�̃N���X*/
class SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^�\
	/// </summary>
	SceneBase();

	/// <summary>
	/// �f�X�g���N�^�\
	/// </summary>
	virtual ~SceneBase();

	/// <summary>
	/// Scene�X�V����
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <returns>���݂̃V�[���̃|�C���^</returns>
	virtual SceneBase* Update(float deltaTime) = 0;

	/// <summary>
	/// �V�[���̕`��
	/// </summary>
	virtual void Draw() = 0;

protected:
	int BgHandle;		//�w�i�摜�n���h��
	int BgX;			//�w�i���WX
	int BgY;			//�w�i���WY
};

