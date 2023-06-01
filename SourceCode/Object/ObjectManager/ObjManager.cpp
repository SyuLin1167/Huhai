#include "ObjManager.h"


ObjManager* ObjManager::objInstance = nullptr;				//ObjManager���̂ւ̃|�C���^��`

// @brief ObjManager�R���X�g���N�^�[ //

ObjManager::ObjManager()
	:Object()
	,holdObj()
{
}

// @brief ObjManager�f�X�g���N�^�[ //

ObjManager::~ObjManager()
{
}

// @brief ObjManager���������� //

void ObjManager::Init()
{
	if (!objInstance)										//�|�C���^���󂾂�����
	{
		objInstance = new ObjManager;						//�|�C���^������
	}
}

// @brief �I�u�W�F�N�g�o�^ //

void ObjManager::Entry(ObjectBase* newObj)
{
	objInstance->holdObj.emplace_back(newObj);				//�I�u�W�F�N�g�ꎞ�ۑ�
}

//@brief �I�u�W�F�N�g�폜 //

void ObjManager::Release(ObjectBase* releaseObj)
{
	auto iter = find(objInstance->holdObj.begin(),
		objInstance->holdObj.end(), releaseObj);			//�ꎞ�ۑ��I�u�W�F�N�g��������

	if (iter != objInstance->holdObj.end())					//�I�u�W�F�N�g������������
	{
		iter_swap(iter, objInstance->holdObj.end() - 1);	//�������I�u�W�F�N�g���Ō���Ɉړ�
		objInstance->holdObj.pop_back();					//�f�[�^���폜
		return;
	}

	ObjectTag tag = releaseObj->GetTag();					//����I�u�W�F�N�g�̃^�O��ގ擾

	iter = find(objInstance->Object[tag].begin(),
		objInstance->Object[tag].end(), releaseObj);				//�A�N�e�B�u�I�u�W�F�N�g��������

	if (iter != objInstance->Object[tag].end())					//�I�u�W�F�N�g������������
	{
		iter_swap(iter, objInstance->Object[tag].end() - 1);		//�������I�u�W�F�N�g�𖖔��Ɉړ�
		delete objInstance->Object[tag].back();					//�I�u�W�F�N�g�폜
	}
}

// @brief �S�I�u�W�F�N�g�폜 //

void ObjManager::ReleaseAllObj()
{
	while (!objInstance->holdObj.empty())					//�ꎞ�ۑ��I�u�W�F�N�g������ɂȂ�܂�
	{
		delete objInstance->holdObj.back();					//��������f�[�^�폜
		objInstance->holdObj.pop_back();					//��������v�f�폜
	}

	for (auto& tag : ObjTagAll)					//�A�N�e�B�u�I�u�W�F�N�g������ɂȂ�܂�
	{
		while (!objInstance->Object[tag].empty())				//��łȂ����
		{
			delete objInstance->Object[tag].back();					//��������f�[�^�폜
			objInstance->Object[tag].pop_back();						//��������v�f�폜
		}
	}
}

// @brief �S�I�u�W�F�N�g�̍X�V���� //

void ObjManager::Update(float deltaTime)
{
	//���ׂẴ^�O���ȉ��̏���������
	for (auto& tag : ObjTagAll)
	{
		// �Y���^�O�ɂ��邷�ׂẴI�u�W�F�N�g���X�V
		for (int i = 0; i < objInstance->Object[tag].size(); ++i)
		{
			objInstance->Object[tag][i]->Update(deltaTime);
		}
	}
	for (auto holding : objInstance->holdObj)		//�ꎞ�ۑ����̃I�u�W�F�N�g���A�N�e�B�u���X�g�ɒǉ�
	{
		ObjectTag tag = holding->GetTag();					//����I�u�W�F�N�g�̃^�O��ގ擾
		objInstance->Object[tag].emplace_back(holding);		//�ۑ����̃I�u�W�F�N�g�f�[�^���I�u�W�F�N�g�ֈړ�
	}
	objInstance->holdObj.clear();							//�S�Ĉڂ��I�������ꎞ�ۑ��I�u�W�F�N�g������ɂ���

	Dead();
}

// @brief �I�u�W�F�N�g�̐����� //

void ObjManager::Dead()
{
	vector<ObjectBase*>deadObj;										//���S�I�u�W�F�N�g
	for (auto& tag : ObjTagAll)
	{
			// �^�O�������ׂĉ��A���SObject���������AdeadObjects��
		for (auto obj:objInstance->Object[tag])
		{
			if (!obj->IsAlive())
			{
				deadObj.emplace_back(obj);
			}
		}
		objInstance->Object[tag].erase(remove_if(begin(objInstance->Object[tag]), end(objInstance->Object[tag]),
			[](ObjectBase* dead) {return !dead->IsAlive(); }), cend(objInstance->Object[tag]));
	}

	while (!deadObj.empty())
	{
		delete deadObj.back();
		deadObj.pop_back();
	}
}


// @brief �I�u�W�F�N�g�̕`�揈�� //

void ObjManager::Draw()
{
	for (auto& tag : ObjTagAll)
	{
		for (int i = 0; i < objInstance->Object[tag].size(); ++i)
		{
			if (objInstance->Object[tag][i]->IsVisible())
			{
				objInstance->Object[tag][i]->Draw();
			}

		}
	}
}

// @brief�@�����蔻�菈�� //

void ObjManager::Collision()
{
	//---�����蔻��̑g�ݍ��킹---//
	//---Ghost---//
	for (int gstNum = 0; gstNum < objInstance->Object[ObjectTag::Ghost].size(); ++gstNum)
	{

		for (int mapNum = 0; mapNum < objInstance->Object[ObjectTag::Map].size(); ++mapNum)
		{
			objInstance->Object[ObjectTag::Ghost][gstNum]->
				OnCollisionEnter(objInstance->Object[ObjectTag::Map][mapNum]);
		}
		for (int plyNum = 0; plyNum < objInstance->Object[ObjectTag::Player].size(); ++plyNum)
		{
			objInstance->Object[ObjectTag::Ghost][gstNum]->
				OnCollisionEnter(objInstance->Object[ObjectTag::Player][plyNum]);
		}

	}

	//---Player---//
	for (int plyNum = 0; plyNum < objInstance->Object[ObjectTag::Player].size(); ++plyNum)
	{
		for (int mapNum = 0; mapNum < objInstance->Object[ObjectTag::Map].size(); ++mapNum)
		{
			objInstance->Object[ObjectTag::Player][plyNum]->
				OnCollisionEnter(objInstance->Object[ObjectTag::Map][mapNum]);
		}
		for (int furNum = 0; furNum < objInstance->Object[ObjectTag::Furniture].size(); ++furNum)
		{
			objInstance->Object[ObjectTag::Player][plyNum]->
				OnCollisionEnter(objInstance->Object[ObjectTag::Furniture][furNum]);
		}
		for (int gstNum = 0; gstNum < objInstance->Object[ObjectTag::Ghost].size(); ++gstNum)
		{
			objInstance->Object[ObjectTag::Player][plyNum]->
				OnCollisionEnter(objInstance->Object[ObjectTag::Ghost][gstNum]);
		}
	}
}

// @brief �^�O��̍ŏ��̃I�u�W�F�N�g�擾 //

ObjectBase* ObjManager::GetFirstObj(ObjectTag tag)
{
	if (objInstance->Object[tag].size() == 0)		//�I�u�W�F�N�g�̐���0��������
	{
		return nullptr;								//��Ȃ̂�nullptr��Ԃ�
	}
	return objInstance->Object[tag][0];				//�^�O��̍ŏ��̃I�u�W�F�N�g��Ԃ�
}

// @brief �^�O���tagNum�Ԗڂ̃I�u�W�F�N�g�擾 //

ObjectBase* ObjManager::GetObj(ObjectTag tag, int tagNum)
{
	if (objInstance->Object[tag].size() < static_cast<unsigned long long>(tagNum) + 1)		//�I�u�W�F�N�g�̐����w�萔��菭�Ȃ�������
	{
		return nullptr;								//nullptr��Ԃ�
	}
	return objInstance->Object[tag][tagNum];		//�^�O���tagNum�Ԗڂ̃I�u�W�F�N�g��Ԃ�
}

// @birief ObjManager�̊J�� //

void ObjManager::Finalize()
{
	ReleaseAllObj();										//�S�ẴI�u�W�F�N�g�J��
	if (objInstance)										//objManager�Ɏ��Ԃ���������
	{
		delete objInstance;									//�폜
	}
}
