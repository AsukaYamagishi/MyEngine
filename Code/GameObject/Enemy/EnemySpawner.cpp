#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(DirectXCommon* dxCommon,std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObjectBase(dxCommon)
{
	this->collisionManager = collisionManager;
	playerData = player;
	// �t�@�C���ǂݍ���
	LoadData("Resources/Csv/EnemySpownBlocData.csv");
}

void EnemySpawner::Update()
{
	if (spawnDatas.size() == 0)
	{
		return;
	}
	// �v���C���[���X�|�[���ʒu������̋������ɂ���ΐ擪�̃f�[�^���X�|�[��������
	if (playerData->GetPos().z >= spawnDatas.front().spawnPos.z - 50.0f)
	{
		GameObjectBase::Create<Enemy>(
			dxCommon, gameObjectManager, collisionManager,
			spawnDatas.front().spawnPos, playerData);
		spawnDatas.pop();
	}
}

void EnemySpawner::LoadData(const char* filepath)
{

	ifstream fileStream(filepath);
	if (!fileStream) 
	{
		assert(0);
	}
	// �s
	int i = 0;

	//�t�@�C�����I���܂œǂݍ���
	while (!fileStream.eof())
	{
		i++;
		string bufferString;
		fileStream >> bufferString;
		//1�s�ڂ͗񖼂Ńf�[�^�ł͂Ȃ����߃X�L�b�v
		if (i <= 1) continue;

		//�f�[�^�����ڂ��Ƃɒ��o
		istringstream stringStream(bufferString);
		vector<string> datas;
		string stemp;
		//�J���}��؂�Ńf�[�^��؂蕪��
		while (getline(stringStream, stemp, ','))
		{
			datas.push_back(stemp);
		}

		int type = strtof(datas[3].c_str(), NULL);
		Vector3 startPos
		{
			strtof(datas[0].c_str(),NULL),
			strtof(datas[1].c_str(),NULL),
			strtof(datas[2].c_str(),NULL)
		};
		//�؂蕪�����f�[�^���\���̂Ɋi�[
		switch (type)
		{
		case CROSS:
			CrossSpawn(startPos);
			break;
		case BOX:
			BoxSpawn(startPos);
			break;
		default:
			break;
		}
		
	}
	//�t�@�C���N���[�Y
	fileStream.close();

}

void EnemySpawner::CrossSpawn(Vector3 startPos)
{
	// �^��
	spawnDatas.push(SpawnData{ startPos });
	// �E��
	spawnDatas.push(SpawnData{ startPos + Vector3{10,10,0} });
	// ����
	spawnDatas.push(SpawnData{ startPos + Vector3{-10,10,0} });
	// �E��
	spawnDatas.push(SpawnData{ startPos + Vector3{10,-10,0} });
	// ����
	spawnDatas.push(SpawnData{ startPos + Vector3{-10,-10,0} });
}

void EnemySpawner::BoxSpawn(Vector3 startPos)
{
	// �E��
	spawnDatas.push(SpawnData{ startPos + Vector3{5,5,0} });
	// ����
	spawnDatas.push(SpawnData{ startPos + Vector3{-5,5,0} });
	// �E��
	spawnDatas.push(SpawnData{ startPos + Vector3{5,-5,0} });
	// ����
	spawnDatas.push(SpawnData{ startPos + Vector3{-5,-5,0} });

}
