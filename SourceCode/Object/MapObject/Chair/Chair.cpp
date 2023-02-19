#include "Chair.h"

// @brief Chair�R���X�g���N�^�[ //

Chair::Chair()
	:ObjectBase(ObjectTag::Chair)
	, ChairAnim(nullptr)
{
	Load();
}

// @brief Chair�R���X�g���N�^�[ //

Chair::Chair(VECTOR ChairPos, VECTOR ChairAngle)
	:ObjectBase(ObjectTag::Chair, ChairPos, ChairAngle)
	, ChairAnim(nullptr)
{
	Load();
}

// @brief Chair�f�X�g���N�^�[ //

Chair::~Chair()
{
	AssetManager::ReleaseMesh(objHandle);
	delete ChairAnim;
}

// @brief Chair�ǂݍ��ݏ��� //

void Chair::Load()
{
	//---���f���ǂݍ���---//
	objHandle = AssetManager::GetMesh("../Assets/Map/Chair/Chair.mv1");            //���f���ǂݍ���

	MV1SetPosition(objHandle, objPos);                                                      //���f���̍��W�ݒ�
	MV1SetScale(objHandle, objScale);                                                       //���f���̃T�C�Y�ݒ�
	MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //���f���̌����ݒ�

	//---�C���X�^���X---//
	ChairAnim = new Animation(objHandle);

	//---�A�j���[�V�����ǂݍ���---//
	ChairAnim->AddAnimation("../Assets/Map/Chair/Chair.mv1");                        //�ҋ@:0
	ChairAnim->AddAnimation("../Assets/Map/Chair/ChairMove.mv1", 30.0f, false);      //����:1

	animType = IDLE;
	ChairAnim->StartAnim(animType);

	colType = CollisionType::Sphere;                                                         //�����蔻��͋���

	colSphere.localCenter = VGet(0, 5, 0);                                                 //���[�J�����W
	colSphere.Radius = 15.0f;                                                                //�����a
	colSphere.worldCenter = objPos;                                                          //���[���h���W

}

// @brief Chair�X�V���� //

void Chair::Update(float deltaTime)
{
	ChairAnim->AddAnimTime(deltaTime);


	//---�����蔻��ݒ�---//
	ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);         //�v���C���[�I�u�W�F�N�g�擾
	if (player)                                                              //�I�u�W�F�N�g�̒��g����łȂ����
	{
		if (CollisionPair(colSphere, player->GetColSphere()))
		{
			if (animType != MOVE || animType == IDLE)                                       //�A�j���[�V�����J�����[�V�����łȂ����
			{
				animType = MOVE;                                        //�A�j���[�V�����͊J�����[�V����
				ChairAnim->StartAnim(animType);                               //�J�����[�V�����ŃA�j���[�V�����J�n
			}
		}
	}

	colModel = objHandle;																//�����蔻��̃��f���̓I�u�W�F�N�g�̃��f��
	ColUpdate();

}

// @brief Chair�`�揈�� //

void Chair::Draw()
{
	MV1DrawModel(objHandle);						//���f���`��
}