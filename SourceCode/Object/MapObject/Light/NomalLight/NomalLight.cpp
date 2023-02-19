#include "NomalLight.h"

// @brief Light�R���X�g���N�^�[ //

Light::Light()
	:ObjectBase(ObjectTag::Light)
{
	Load();
}

// @brief Light�R���X�g���N�^�[ //

Light::Light(VECTOR LightPos,bool flash)
	:ObjectBase(ObjectTag::Light, LightPos)
{
	Load();
	if (!flash)
	{
		CreatePointLightHandle(LightPos, 70.0f, 0.0f, 0.0f, 0.003f);   
		MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// @brief Light�f�X�g���N�^�[ //

Light::~Light()
{
	AssetManager::ReleaseMesh(objHandle);
}

// @brief Light�ǂݍ��ݏ��� //

void Light::Load()
{
    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");            //���f���ǂݍ���

    MV1SetPosition(objHandle, objPos);                                                      //���f���̍��W�ݒ�
    MV1SetScale(objHandle, objScale);                                                       //���f���̃T�C�Y�ݒ�
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //���f���̌����ݒ�

    //---�����蔻��---//
    colType = CollisionType::Sphere;                                                         //�����蔻��͋���

    colSphere.localCenter = VGet(0, -5, 0);                                                 //���[�J�����W
    colSphere.Radius = 15.0f;                                                                //�����a
    colSphere.worldCenter = objPos;                                                          //���[���h���W

}

// @brief Light�X�V���� //

void Light::Update(float deltaTime)
{

	//---�����蔻��ݒ�---//
	ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);         //�v���C���[�I�u�W�F�N�g�擾
	if (player)                                                              //�I�u�W�F�N�g�̒��g����łȂ����
	{
		if (CollisionPair(colSphere, player->GetColSphere()))
		{
		}
	}
	VECTOR distance = player->GetPos()-objPos;
	if (abs(distance.x * distance.x + distance.y + distance.y) < 10)
	{
		CreatePointLightHandle(objPos, 70.0f, 0.0f, 0.0f, 0.01f);
		MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}

	colModel = objHandle;																//�����蔻��̃��f���̓I�u�W�F�N�g�̃��f��
	ColUpdate();

}

void Light::Flash(float deltaTime)
{
	srand((unsigned int)time(NULL));
	if (flashTime<=lightTimer)
	{
		lightTimer += deltaTime;
	}
	else
	{

		flashTime = rand() % 2;
		
		lightTimer = 0;
		isFlash = !isFlash;
	}

	//if (isFlash)
	//{
	//	MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	//}
}

// @brief Light�`�揈�� //

void Light::Draw()
{
	MV1DrawModel(objHandle);						//���f���`��
	DrawFormatString(0, 150, GetColor(255, 255, 255), "%d", isFlash);
	ColDraw();
}