#include "Door.h"

// @brief Door�R���X�g���N�^�[ //

Door::Door()
    :ObjectBase(ObjectTag::Door)
    ,doorAnim(nullptr)
{
    Load();
}

// @brief Door�R���X�g���N�^�[ //

Door::Door(VECTOR doorPos,VECTOR doorAngle)
    :ObjectBase(ObjectTag::Door,doorPos,doorAngle)
    ,doorAnim(nullptr)
{
    Load();
}

// @brief Door�f�X�g���N�^�[ //

Door::~Door()
{
    AssetManager::ReleaseMesh(objHandle);
    delete doorAnim;
}

// @brief Door�ǂݍ��ݏ��� //

void Door::Load()
{
    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Door/Door.mv1");            //���f���ǂݍ���

    MV1SetPosition(objHandle, objPos);                                                      //���f���̍��W�ݒ�
    MV1SetScale(objHandle, objScale);                                                       //���f���̃T�C�Y�ݒ�
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //���f���̌����ݒ�

    //---�C���X�^���X---//
    doorAnim = new Animation(objHandle);

    //---�A�j���[�V�����ǂݍ���---//
    doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/Door.mv1");                        //�ҋ@:0
    doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/DoorOpen.mv1", 30.0f, false);      //�J:1
    doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/DoorClose.mv1", 30.0f, false);     //��:2

	animType = IDLE;
	doorAnim->StartAnim(animType);

	colType = CollisionType::Sphere;                                                         //�����蔻��͋���

	colSphere.localCenter = VGet(0, 5, 0);                                                 //���[�J�����W
	colSphere.Radius = 15.0f;                                                                //�����a
	colSphere.worldCenter = objPos;                                                          //���[���h���W

}

// @brief Door�X�V���� //

void Door::Update(float deltaTime)
{
	doorAnim->AddAnimTime(deltaTime);	


	//---�����蔻��ݒ�---//
	player = ObjManager::GetFirstObj(ObjectTag::Player);         //�v���C���[�I�u�W�F�N�g�擾
	if (player)                                                              //�I�u�W�F�N�g�̒��g����łȂ����
	{
		if (CollisionPair(colSphere, player->GetColSphere()))
		{
			if (CheckHitKey(KEY_INPUT_E))                //E�L�[����
			{
				if (animType != OPEN || animType == IDLE)                                       //�A�j���[�V�����J�����[�V�����łȂ����
				{
					animType = OPEN;                                        //�A�j���[�V�����͊J�����[�V����
					doorAnim->StartAnim(animType);                               //�J�����[�V�����ŃA�j���[�V�����J�n
				}
			}
			if (CheckHitKey(KEY_INPUT_Q))                //Q�L�[����
			{

				if (animType = OPEN)                                       //�A�j���[�V�������J�����[�V������������
				{
					animType = CLOSE;                                        //�A�j���[�V�����͕��郂�[�V����
					doorAnim->StartAnim(animType);                               //���郂�[�V�����ŃA�j���[�V�����J�n
				}
			}
		}

	}
	colModel = objHandle;																//�����蔻��̃��f���̓I�u�W�F�N�g�̃��f��
	ColUpdate();
	
}

// @brief Door�`�揈�� //

void Door::Draw()
{
	MV1DrawModel(objHandle);						//���f���`��
	ColDraw();
}